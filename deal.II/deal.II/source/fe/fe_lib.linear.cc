/* $Id$ */

#include <fe/fe_lib.h>
#include <grid/tria_iterator.h>
#include <grid/dof_accessor.h>
#include <algorithm>



FELinear<1>::FELinear () :
		FiniteElement<1> (1, 0)
{
				   // for restriction and prolongation matrices:
				   // note that we do not add up all the
				   // contributions since then we would get
				   // two summands per vertex in 1d (four
				   // in 2d, etc), but only one per line dof.
				   // We could accomplish for that by dividing
				   // the vertex dof values by 2 (4, etc), but
				   // would get into trouble at the boundary
				   // of the domain since there only one
				   // cell contributes to a vertex. Rather,
				   // we do not add up the contributions but
				   // set them right into the matrices!
  restriction[0](0,0) = 1.0;
  restriction[0](0,1) = 1./2.;
  restriction[0](1,1) = 1./2.;

  restriction[1](0,0) = 1./2.;
  restriction[1](1,0) = 1./2.;
  restriction[1](1,1) = 1.0;

  prolongation[0](0,0) = 1.0;
  prolongation[0](1,0) = 1./2.;
  prolongation[0](1,1) = 1./2.;

  prolongation[1](0,0) = 1./2.;
  prolongation[1](0,1) = 1./2.;
  prolongation[1](1,1) = 1.0;
};



double
FELinear<1>::shape_value(const unsigned int i,
			 const Point<1>& p) const
{
  Assert((i<total_dofs), ExcInvalidIndex(i));
  switch (i)
    {
    case 0: return 1.-p(0);
    case 1: return p(0);
    }
  return 0.;
}



Point<1>
FELinear<1>::shape_grad(const unsigned int i,
			const Point<1>&) const
{
  Assert((i<total_dofs), ExcInvalidIndex(i));
  switch (i)
    {
    case 0: return Point<1>(-1.);
    case 1: return Point<1>(1.);
    }
  return Point<1>();
}



void FELinear<1>::fill_fe_values (const DoFHandler<1>::cell_iterator &cell,
				  const vector<Point<1> >            &unit_points,
				  vector<dFMatrix>  &jacobians,
				  const bool         compute_jacobians,
				  vector<Point<1> > &ansatz_points,
				  const bool         compute_ansatz_points,
				  vector<Point<1> > &q_points,
				  const bool         compute_q_points,
				  const Boundary<1> &boundary) const {
				   // simply pass down
  FiniteElement<1>::fill_fe_values (cell, unit_points,
				    jacobians, compute_jacobians,
				    ansatz_points, compute_ansatz_points,
				    q_points, compute_q_points, boundary);
};



void FELinear<1>::get_face_ansatz_points (const typename DoFHandler<1>::face_iterator &,
					  const Boundary<1>  &,
					  vector<Point<1> >  &) const {
  Assert (false, ExcInternalError());
};



void FELinear<1>::get_face_jacobians (const DoFHandler<1>::face_iterator &,
				      const Boundary<1>         &,
				      const vector<Point<0> > &,
				      vector<double>      &) const {
  Assert (false, ExcInternalError());
};



FELinear<2>::FELinear () :
		FiniteElement<2> (1, 0, 0)
{
  interface_constraints(0,0) = 1./2.;
  interface_constraints(0,1) = 1./2.;

  restriction[0](0,0) = 1.0;
  restriction[0](0,1) = 1./2.;
  restriction[0](1,1) = 1./2.;
  restriction[0](0,3) = 1./2.;
  restriction[0](3,3) = 1./2.;
  restriction[0](0,2) = 1./4.;
  restriction[0](1,2) = 1./4.;
  restriction[0](2,2) = 1./4.;
  restriction[0](3,2) = 1./4.;

  restriction[1](1,1) = 1.0;
  restriction[1](0,0) = 1./2.;
  restriction[1](1,0) = 1./2.;
  restriction[1](1,2) = 1./2.;
  restriction[1](2,2) = 1./2.;
  restriction[1](0,3) = 1./4.;
  restriction[1](1,3) = 1./4.;
  restriction[1](2,3) = 1./4.;
  restriction[1](3,3) = 1./4.;

  restriction[2](2,2) = 1.0;
  restriction[2](2,1) = 1./2.;
  restriction[2](1,1) = 1./2.;
  restriction[2](2,3) = 1./2.;
  restriction[2](3,3) = 1./2.;
  restriction[2](0,0) = 1./4.;
  restriction[2](1,0) = 1./4.;
  restriction[2](2,0) = 1./4.;
  restriction[2](3,0) = 1./4.;

  restriction[3](3,3) = 1.0;
  restriction[3](0,0) = 1./2.;
  restriction[3](3,0) = 1./2.;
  restriction[3](2,2) = 1./2.;
  restriction[3](3,2) = 1./2.;
  restriction[3](0,1) = 1./4.;
  restriction[3](1,1) = 1./4.;
  restriction[3](2,1) = 1./4.;
  restriction[3](3,1) = 1./4.;

  prolongation[0](0,0) = 1.0;
  prolongation[0](1,0) = 1./2.;
  prolongation[0](1,1) = 1./2.;
  prolongation[0](3,0) = 1./2.;
  prolongation[0](3,3) = 1./2.;
  prolongation[0](2,0) = 1./4.;
  prolongation[0](2,1) = 1./4.;
  prolongation[0](2,2) = 1./4.;
  prolongation[0](2,3) = 1./4.;

  prolongation[1](1,1) = 1.0;
  prolongation[1](0,0) = 1./2.;
  prolongation[1](0,1) = 1./2.;
  prolongation[1](2,1) = 1./2.;
  prolongation[1](2,2) = 1./2.;
  prolongation[1](3,0) = 1./4.;
  prolongation[1](3,1) = 1./4.;
  prolongation[1](3,2) = 1./4.;
  prolongation[1](3,3) = 1./4.;

  prolongation[2](2,2) = 1.0;
  prolongation[2](1,2) = 1./2.;
  prolongation[2](1,1) = 1./2.;
  prolongation[2](3,2) = 1./2.;
  prolongation[2](3,3) = 1./2.;
  prolongation[2](0,0) = 1./4.;
  prolongation[2](0,1) = 1./4.;
  prolongation[2](0,2) = 1./4.;
  prolongation[2](0,3) = 1./4.;

  prolongation[3](3,3) = 1.0;
  prolongation[3](0,0) = 1./2.;
  prolongation[3](0,3) = 1./2.;
  prolongation[3](2,2) = 1./2.;
  prolongation[3](2,3) = 1./2.;
  prolongation[3](1,0) = 1./4.;
  prolongation[3](1,1) = 1./4.;
  prolongation[3](1,2) = 1./4.;
  prolongation[3](1,3) = 1./4.;
};



double
FELinear<2>::shape_value (const unsigned int i,
			  const Point<2>& p) const
{
  Assert((i<total_dofs), ExcInvalidIndex(i));
  switch (i)
    {
    case 0: return (1.-p(0)) * (1.-p(1));
    case 1: return p(0) * (1.-p(1));
    case 2: return p(0) * p(1);
    case 3: return (1.-p(0)) * p(1);
    }
  return 0.;
}



Point<2>
FELinear<2>::shape_grad (const unsigned int i,
			 const Point<2>& p) const
{
  Assert((i<total_dofs), ExcInvalidIndex(i));
  switch (i)
    {
    case 0: return Point<2> (p(1)-1., p(0)-1.);
    case 1: return Point<2> (1.-p(1), -p(0));
    case 2: return Point<2> (p(1), p(0));
    case 3: return Point<2> (-p(1), 1.-p(0));
    }
  return Point<2> ();
}



template <int dim>
void FELinear<dim>::fill_fe_values (const DoFHandler<dim>::cell_iterator &cell,
				    const vector<Point<dim> >            &unit_points,
				    vector<dFMatrix>    &jacobians,
				    const bool           compute_jacobians,
				    vector<Point<dim> > &ansatz_points,
				    const bool           compute_ansatz_points,
				    vector<Point<dim> > &q_points,
				    const bool           compute_q_points,
				    const Boundary<dim> &) const {
  Assert (jacobians.size() == unit_points.size(),
	  ExcWrongFieldDimension(jacobians.size(), unit_points.size()));
  Assert (q_points.size() == unit_points.size(),
	  ExcWrongFieldDimension(q_points.size(), unit_points.size()));
  Assert (ansatz_points.size() == total_dofs,
	  ExcWrongFieldDimension(ansatz_points.size(), total_dofs));
  
  const unsigned int n_vertices=(1<<dim);
  unsigned int n_points=unit_points.size();

  Point<dim> vertices[n_vertices];
  for (unsigned int l=0; l<n_vertices; ++l)
    vertices[l] = cell->vertex(l);
  

  if (compute_q_points) 
    {
				       // initialize points to zero
      for (unsigned int i=0; i<n_points; ++i)
	q_points[i] = Point<dim> ();
      
				       // note: let x_l be the vector of the
				       // lth quadrature point in real space and
				       // xi_l that on the unit cell, let further
				       // p_j be the vector of the jth vertex
				       // of the cell in real space and
				       // N_j(xi_l) be the value of the associated
				       // basis function at xi_l, then
				       // x_l(xi_l) = sum_j p_j N_j(xi_l)
      for (unsigned int j=0; j<n_vertices; ++j) 
	for (unsigned int l=0; l<n_points; ++l) 
	  q_points[l] += vertices[j] * shape_value(j, unit_points[l]);
    };
  

/* jacobi matrices: compute d(x)/d(xi) and invert this
   Let M(l) be the inverse of J at the quadrature point l, then
     M_{ij}(l) = sum_s p_i(s) d(N_s(l))/d(xi_j)
   where p_i(s) is the i-th coordinate of the s-th vertex vector,
   N_s(l) is the value of the s-th vertex shape function at the
   quadrature point l.

   We could therefore write:
   l=0..n_points-1
     i=0..dim-1
       j=0..dim-1
         M_{ij}(l) = 0
	 s=0..n_vertices
	   M_{ij}(l) += p_i(s) d(N_s(l))/d(xi_j)

  However, we rewrite the loops to only compute the gradient once for
  each integration point and basis function.
*/
  if (compute_jacobians) 
    {
      dFMatrix M(dim,dim);
      for (unsigned int l=0; l<n_points; ++l) 
	{
	  M.clear ();
	  for (unsigned int s=0; s<n_vertices; ++s)
	    {
					       // we want a linear transform and
					       // if we prepend the class name in
					       // front of the #shape_grad#, we
					       // need not use virtual function
					       // calls.
	      const Point<dim> gradient
		= FELinear<dim>::shape_grad (s, unit_points[l]);
	      for (unsigned int i=0; i<dim; ++i)
		for (unsigned int j=0; j<dim; ++j)
		  M(i,j) += vertices[s](i) * gradient(j);
	    };
	  jacobians[l].invert(M);
	};
    };

				   // compute ansatz points, which are
				   // the corners for linear elements
  if (compute_ansatz_points) 
    for (unsigned int vertex=0; vertex<n_vertices; ++vertex)
      ansatz_points[vertex] = vertices[vertex];
};




template <int dim>
void FELinear<dim>::get_face_ansatz_points (const typename DoFHandler<dim>::face_iterator &face,
					    const Boundary<dim>  &,
					    vector<Point<dim> >  &ansatz_points) const {
  Assert (ansatz_points.size() == (1<<(dim-1)),
	  ExcWrongFieldDimension (ansatz_points.size(), 1<<(dim-1)));

  for (unsigned int vertex=0; vertex<(1<<(dim-1)); ++vertex)
    ansatz_points[vertex] = face->vertex(vertex);
};



void FELinear<2>::get_face_jacobians (const DoFHandler<2>::face_iterator &face,
				      const Boundary<2>         &,
				      const vector<Point<1> > &unit_points,
				      vector<double>      &face_jacobians) const {
  Assert (unit_points.size() == face_jacobians.size(),
	  ExcWrongFieldDimension (unit_points.size(), face_jacobians.size()));

				   // a linear mapping for a single line
				   // produces particularly simple
				   // expressions for the jacobi
				   // determinant :-)
  const double h = sqrt((face->vertex(1) - face->vertex(0)).square());
  fill_n (face_jacobians.begin(),
	  unit_points.size(),
	  h);  
};






FEQuadratic<1>::FEQuadratic () :
		FiniteElement<1> (1, 1) {};



void FEQuadratic<1>::fill_fe_values (const DoFHandler<1>::cell_iterator &cell,
				     const vector<Point<1> >            &unit_points,
				     vector<dFMatrix>  &jacobians,
				     const bool         compute_jacobians,
				     vector<Point<1> > &ansatz_points,
				     const bool         compute_ansatz_points,
				     vector<Point<1> > &q_points,
				     const bool         compute_q_points,
				     const Boundary<1> &boundary) const {
				   // simply pass down
  FiniteElement<1>::fill_fe_values (cell, unit_points,
				    jacobians, compute_jacobians,
				    ansatz_points, compute_ansatz_points,
				    q_points, compute_q_points, boundary);
};



void FEQuadratic<1>::get_face_ansatz_points (const typename DoFHandler<1>::face_iterator &,
					     const Boundary<1>  &,
					     vector<Point<1> >  &) const {
  Assert (false, ExcInternalError());
};



void FEQuadratic<1>::get_face_jacobians (const DoFHandler<1>::face_iterator &,
					 const Boundary<1>         &,
					 const vector<Point<0> > &,
					 vector<double>      &) const {
  Assert (false, ExcInternalError());
};



FEQuadratic<2>::FEQuadratic () :
		FiniteElement<2> (1, 1, 1)
{
  interface_constraints(0,2) = 1.0;
  interface_constraints(1,0) = 3./8.;
  interface_constraints(1,1) = -1./8.;
  interface_constraints(1,2) = 3./4.;
  interface_constraints(2,0) = -1./8.;
  interface_constraints(2,1) = 3./8.;
  interface_constraints(2,2) = 3./4.;

				   // still implement restriction
				   // and prolongation
  Assert (false, ExcNotImplemented());
};



template <int dim>
double
FEQuadratic<dim>::shape_value (const unsigned int i,
			       const Point<dim> &) const
{
  Assert (i<total_dofs, typename FiniteElementBase<dim>::ExcInvalidIndex(i));
  Assert (false, ExcNotImplemented());
  return 0.;
};



template <int dim>
Point<dim>
FEQuadratic<dim>::shape_grad (const unsigned int i,
			      const Point<dim> &) const
{
  Assert (i<total_dofs, typename FiniteElementBase<dim>::ExcInvalidIndex(i));
  Assert (false, ExcNotImplemented());
  return Point<dim> ();
};



template <int dim>
void FEQuadratic<dim>::fill_fe_values (const DoFHandler<dim>::cell_iterator &,
				       const vector<Point<dim> >            &unit_points,
				       vector<dFMatrix>  &jacobians,
				       const bool,
				       vector<Point<dim> > &ansatz_points,
				       const bool,
				       vector<Point<dim> > &q_points,
				       const bool,
				       const Boundary<dim> &) const {
  Assert (jacobians.size() == unit_points.size(),
	  ExcWrongFieldDimension(jacobians.size(), unit_points.size()));
  Assert (q_points.size() == unit_points.size(),
	  ExcWrongFieldDimension(q_points.size(), unit_points.size()));
  Assert (ansatz_points.size() == total_dofs,
	  ExcWrongFieldDimension(ansatz_points.size(), total_dofs));

  Assert (false, ExcNotImplemented());
};



template <int dim>
void FEQuadratic<dim>::get_face_ansatz_points (const typename DoFHandler<dim>::face_iterator &,
					       const Boundary<dim>  &,
					       vector<Point<dim> >  &) const {
  Assert (false, ExcNotImplemented());
};



template <int dim>
void FEQuadratic<dim>::get_face_jacobians (const DoFHandler<dim>::face_iterator &,
				      const Boundary<dim>         &,
				      const vector<Point<dim-1> > &,
				      vector<double>      &) const {
  Assert (false, ExcNotImplemented());
};






FECubic<1>::FECubic () :
		FiniteElement<1> (1, 2) {};



void FECubic<1>::fill_fe_values (const DoFHandler<1>::cell_iterator &cell,
				 const vector<Point<1> >            &unit_points,
				 vector<dFMatrix>  &jacobians,
				 const bool         compute_jacobians,
				 vector<Point<1> > &ansatz_points,
				 const bool         compute_ansatz_points,
				 vector<Point<1> > &q_points,
				 const bool         compute_q_points,
				 const Boundary<1> &boundary) const {
				   // simply pass down
  FiniteElement<1>::fill_fe_values (cell, unit_points,
				    jacobians, compute_jacobians,
				    ansatz_points, compute_ansatz_points,
				    q_points, compute_q_points, boundary);
};



void FECubic<1>::get_face_ansatz_points (const typename DoFHandler<1>::face_iterator &,
					 const Boundary<1>  &,
					 vector<Point<1> >  &) const {
  Assert (false, ExcInternalError());
};



void FECubic<1>::get_face_jacobians (const DoFHandler<1>::face_iterator &,
				     const Boundary<1>         &,
				     const vector<Point<0> > &,
				     vector<double>      &) const {
  Assert (false, ExcInternalError());
};




FECubic<2>::FECubic () :
		FiniteElement<2> (1, 2, 4) {};




template <int dim>
double
FECubic<dim>::shape_value (const unsigned int i,
			   const Point<dim> &) const
{
  Assert (i<total_dofs, typename FiniteElementBase<dim>::ExcInvalidIndex(i));
  Assert (false, ExcNotImplemented());
  return 0.;
};



template <int dim>
Point<dim>
FECubic<dim>::shape_grad (const unsigned int i,
			  const Point<dim> &) const
{
  Assert (i<total_dofs, typename FiniteElementBase<dim>::ExcInvalidIndex(i));
  Assert (false, ExcNotImplemented());
  return Point<dim> ();
};



template <int dim>
void FECubic<dim>::fill_fe_values (const DoFHandler<dim>::cell_iterator &,
				   const vector<Point<dim> >            &unit_points,
				   vector<dFMatrix>  &jacobians,
				   const bool,
				   vector<Point<dim> > &ansatz_points,
				   const bool,
				   vector<Point<dim> > &q_points,
				   const bool,
				   const Boundary<dim> &) const {
  Assert (jacobians.size() == unit_points.size(),
	  ExcWrongFieldDimension(jacobians.size(), unit_points.size()));
  Assert (q_points.size() == unit_points.size(),
	  ExcWrongFieldDimension(q_points.size(), unit_points.size()));
  Assert (ansatz_points.size() == total_dofs,
	  ExcWrongFieldDimension(ansatz_points.size(), total_dofs));

  Assert (false, ExcNotImplemented());
};



template <int dim>
void FECubic<dim>::get_face_ansatz_points (const typename DoFHandler<dim>::face_iterator &,
					   const Boundary<dim>  &,
					   vector<Point<dim> >  &) const {
  Assert (false, ExcNotImplemented());
};



template <int dim>
void FECubic<dim>::get_face_jacobians (const DoFHandler<dim>::face_iterator &,
				       const Boundary<dim>         &,
				       const vector<Point<dim-1> > &,
				       vector<double>      &) const {
  Assert (false, ExcNotImplemented());
};




// explicit instantiations

template class FELinear<1>;
template class FELinear<2>;
template class FEQuadratic<1>;
template class FEQuadratic<2>;
template class FECubic<1>;
template class FECubic<2>;

