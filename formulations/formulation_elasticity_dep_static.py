# -*- coding: utf-8 -*-
f_vol = Variable( interpolation='global', nb_dim=[dim], default_value='0.0,'*(dim-1)+'0.0', unit='N/m^3' )
elastic_modulus = Variable( interpolation='global', default_value='210e9', unit='N/m^2' ) #
poisson_ratio = Variable( interpolation='global', default_value='0.33', unit='1' ) # 
density = Variable( interpolation='global', default_value='7800', unit='kg/m^3' ) # 

dep = Variable( unknown=True, nb_dim=[dim], default_value='0.0', unit='m' )

sigma = Variable( interpolation='der_nodal', default_value='0', nb_dim=[dim*(dim+1)/2], unit='N/m^2' )
epsilon = Variable( interpolation='der_nodal', default_value='0', nb_dim=[dim*(dim+1)/2], unit='1' )
tr_epsilon = Variable( interpolation='der_nodal', default_value='0', unit='1' )

f_nodal = Variable( nb_dim=[dim], nb_der=0, default_value='0.0,'*(dim-1)+'0.0', unit='N' )
f_surf = Variable( nb_dim=[dim], default_value='0.0,'*(dim-1)+'0.0', unit='N/m^2' )


# --------------------------------------------------------------------------------------------------------------------------------
def formulation():
  epsilon = grad_sym_col(dep.expr)
  epstest = grad_sym_col(dep.test)
  
  sigma = mul( hooke_isotrope( elastic_modulus.expr, poisson_ratio.expr, dim, options['behavior_simplification'] )[0] , epsilon )
  
  res = density.expr * dot( f_vol.expr, dep.test )
  for i in range(dim): res += sigma[i] * epstest[i]
  for i in range(dim,epsilon.size()): res += 2 * sigma[i] * epstest[i]

  #
  return res * dSubInter
  #res = e.sub_integration( res )
  #return res * dV + dot( f_nodal.expr, dep.test ) * dN + dot( f_surf.expr, dep.test ) * dS + sub_integration( self, val, order ) * dSubInter

 
# --------------------------------------------------------------------------------------------------------------------------------
def apply_on_elements_after_solve(unk_subs): # return a string
    epsilon = grad_sym_col(dep.expr)
    tr_epsilon = sum([ epsilon[i] for i in range(dim) ])
    sigma = mul( hooke_isotrope( elastic_modulus.expr, poisson_ratio.expr, dim, options['behavior_simplification'] )[0] , epsilon )
    
    my_subs = unk_subs
    #my_subs[ time ] = time_steps[0]
    for vi in e.var_inter: my_subs[vi] = number(0.5)
    
    sigma = sigma.subs(EM(my_subs))
    epsilon = epsilon.subs(EM(my_subs))
    tr_epsilon = tr_epsilon.subs(EM(my_subs))
    
    cw = Write_code('T')
    cw.add( tr_epsilon, 'elem.tr_epsilon', Write_code.Set )
    for i in range(dim*(dim+1)/2):
        cw.add( sigma[i], 'elem.sigma[0]['+str(i)+']', Write_code.Set )
        cw.add( epsilon[i], 'elem.epsilon[0]['+str(i)+']', Write_code.Set )
    return cw.to_string()

