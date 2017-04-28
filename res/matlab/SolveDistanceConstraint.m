function [ p1, p2 ] = SolveDistanceConstraint( p1, p2, d )
%SOLVEDISTANCECONSTRAINT Summary of this function goes here
%   Detailed explanation goes here

    dir = p2 - p1;
    dist = norm( p2 - p1 );
    diff = dist - d;
    dir = dir .* ( 0.5 * diff / dist );
    p1 = p1 + dir;
    p2 = p2 - dir;

end

