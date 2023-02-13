%
% Copyright (c) 2022 University of Colorado
% Licensed under the MIT license. See LICENSE.txt file in the MORIS root for details.
%
%------------------------------------------------------------------------------------
%

function [ NodalPoints ] = get_nodal_points( d, p )
%GET_NODAL_POINTS Get the nodal points for a tensor-product Lagrange 
%element on parent domain [-1,1]^d
%   d - number of spatial dimensions
%   p - polynomial order

%% Nodal Points for Parent Element [-1,1]^d

% QUAD 4
if ( d == 2 && p == 1 )
    
    NodalPoints = [ ...
        -1.0, -1.0; ...
         1.0, -1.0; ...
         1.0,  1.0; ...
        -1.0,  1.0 ];
    
% QUAD 9
elseif ( d == 2 && p == 2 )
    
    NodalPoints = [ ...
        -1.0, -1.0; ...
         1.0, -1.0; ...
         1.0,  1.0; ...
        -1.0,  1.0; ...
         0.0, -1.0; ...
         1.0,  0.0; ...
         0.0,  1.0; ...
        -1.0,  0.0; ...
         0.0,  0.0 ];
    
% QUAD 16
elseif ( d == 2 && p == 3 )

    c = 1.0/3.0;
    NodalPoints = [ ...
        -1.0, -1.0; ...
         1.0, -1.0; ...
         1.0,  1.0; ...
        -1.0,  1.0; ...
          -c, -1.0; ...
           c, -1.0; ...
         1.0,   -c; ...
         1.0,    c; ...
           c,  1.0; ...
          -c,  1.0; ...
        -1.0,    c; ...
        -1.0,   -c; ...
          -c,   -c; ...
           c,   -c; ...
           c,    c; ...
          -c,    c ];

% HEX 8
elseif ( d == 3 && p == 1 )

    NodalPoints = [ ...
        -1.0, -1.0, -1.0; ...
         1.0, -1.0, -1.0; ...
         1.0,  1.0, -1.0; ...
        -1.0,  1.0, -1.0; ...
        -1.0, -1.0,  1.0; ...
         1.0, -1.0,  1.0; ...
         1.0,  1.0,  1.0; ...
        -1.0,  1.0,  1.0 ];

% HEX 27
elseif ( d == 3 && p == 2 )

    NodalPoints = [ ...
        -1.0, -1.0, -1.0; ...
         1.0, -1.0, -1.0; ...
         1.0,  1.0, -1.0; ...
        -1.0,  1.0, -1.0; ...
        -1.0, -1.0,  1.0; ...
         1.0, -1.0,  1.0; ...
         1.0,  1.0,  1.0; ...
        -1.0,  1.0,  1.0; ...
         0.0, -1.0, -1.0; ...
         1.0,  0.0, -1.0; ...
         0.0,  1.0, -1.0; ...
        -1.0,  0.0, -1.0; ...
        -1.0, -1.0,  0.0; ...
         1.0, -1.0,  0.0; ...
         1.0,  1.0,  0.0; ...
        -1.0,  1.0,  0.0; ...
         0.0, -1.0,  1.0; ...
         1.0,  0.0,  1.0; ...
         0.0,  1.0,  1.0; ...
        -1.0,  0.0,  1.0; ...
         0.0,  0.0,  0.0; ...
         0.0,  0.0, -1.0; ...
         0.0,  0.0,  1.0; ...
        -1.0,  0.0,  0.0; ...
         1.0,  0.0,  0.0; ...
         0.0, -1.0,  0.0; ...
         0.0,  1.0,  0.0 ];    
    
% HEX 64
elseif ( d == 3 && p == 3 )
    
    c = 1.0/3.0;
    NodalPoints = [ ...
        -1.0, -1.0, -1.0; ...
         1.0, -1.0, -1.0; ...
         1.0,  1.0, -1.0; ...
        -1.0,  1.0, -1.0; ...
        -1.0, -1.0,  1.0; ...
         1.0, -1.0,  1.0; ...
         1.0,  1.0,  1.0; ...
        -1.0,  1.0,  1.0; ...
          -c, -1.0, -1.0; ...
           c, -1.0, -1.0; ...
        -1.0,   -c, -1.0; ...
        -1.0,    c, -1.0; ...
        -1.0, -1.0,   -c; ...
        -1.0, -1.0,    c; ...
         1.0,   -c, -1.0; ...
         1.0,    c, -1.0; ...
         1.0, -1.0,   -c; ...
         1.0, -1.0,    c; ...
           c,  1.0, -1.0; ...
          -c,  1.0, -1.0; ...
         1.0,  1.0,   -c; ...
         1.0,  1.0,    c; ...
        -1.0,  1.0,   -c; ...
        -1.0,  1.0,    c; ...
          -c, -1.0,  1.0; ...
           c, -1.0,  1.0; ...
        -1.0,   -c,  1.0; ...
        -1.0,    c,  1.0; ...
         1.0,   -c,  1.0; ...
         1.0,    c,  1.0; ...
           c,  1.0,  1.0; ...
          -c,  1.0,  1.0; ...
          -c,   -c, -1.0; ...
          -c,    c, -1.0; ...
           c,    c, -1.0; ...
           c,   -c, -1.0; ...
          -c, -1.0,   -c; ...
           c, -1.0,   -c; ...
           c, -1.0,    c; ...
          -c, -1.0,    c; ...
        -1.0,   -c,   -c; ...
        -1.0,   -c,    c; ...
        -1.0,    c,    c; ...
        -1.0,    c,   -c; ...
         1.0,   -c,   -c; ...
         1.0,    c,   -c; ...
         1.0,    c,    c; ...
         1.0,   -c,    c; ...
           c,  1.0,   -c; ...
          -c,  1.0,   -c; ...
          -c,  1.0,    c; ...
           c,  1.0,    c; ...
          -c,   -c,  1.0; ...
           c,   -c,  1.0; ...
           c,    c,  1.0; ...
          -c,    c,  1.0; ...
          -c,   -c,   -c; ...
           c,   -c,   -c; ...
           c,    c,   -c; ...
          -c,    c,   -c; ...
          -c,   -c,    c; ...
           c,   -c,    c; ...
           c,    c,    c; ...
          -c,    c,    c ];
      
else
    assert( false, 'get_nodal_points() - Unknown element type.' );
end

%% return NodalPoints
end