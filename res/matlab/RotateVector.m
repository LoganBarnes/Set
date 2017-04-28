function [ rotVec ] = RotateVector( vec, angle, axis )
%ROTATEVECTOR Summary of this function goes here
%   Detailed explanation goes here

    if nargin < 3
        axis = [ 0 0 1 ];
    end
    
    x = vec(1);
    y = vec(2);
    z = vec(3);

    u = axis(1);
    v = axis(2);
    w = axis(3);
    
    cosA = cos(angle);
    sinA = sin(angle);
    
    rotVec = [ -u*(-u*x-v*y-w*z)*(1-cosA) + x*cosA + (-w*y+v*z)*sinA, ...
               -v*(-u*x-v*y-w*z)*(1-cosA) + y*cosA + ( w*x-u*z)*sinA, ...
               -w*(-u*x-v*y-w*z)*(1-cosA) + z*cosA + (-v*x+u*y)*sinA ];
    
    if size(vec,1) > 1
        rotVec = rotVec';
    end
    
end

