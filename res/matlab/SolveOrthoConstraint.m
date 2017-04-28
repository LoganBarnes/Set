function [ points ] = SolveOrthoConstraint( points, r1, r2 )
%SOLVEANGLECONSTRAINT Summary of this function goes here
%   Detailed explanation goes here

    p11 = points(r1(1),:);
    p12 = points(r1(2),:);
    p21 = points(r2(1),:);
    p22 = points(r2(2),:);
%     disp(['p11:',mat2str(p11),';p12:',mat2str(p12),';p21:',mat2str(p21),';p22:',mat2str(p22)]);

    % direction vecs
    v1 = p12 - p11;
    v2 = p22 - p21;
    
    v2len = norm( v2 );

    % normalize
    v1 = Normalize( [v1 0] );
    v2 = Normalize( [v2 0] );
%     disp(['v1:',mat2str(v1),';v2:',mat2str(v2)]);

    normProj = dot( v1, v2 ) * v1;
    perpProj = v2 - normProj;
    
    if norm( perpProj ) < 1e-7
        points(r2(1,2),:) = [ -v2(2), v2(1) ] * v2len + p21;
    else
        points(r2(1,2),:) = Normalize( perpProj(1:2) ) * v2len + p21;
    end

%     p11 = points(r1(1,1),:);
%     p12 = points(r1(1,2),:);
%     p21 = points(r2(1,1),:);
%     p22 = points(r2(1,2),:);
%     disp(['p11:',mat2str(p11),';p12:',mat2str(p12),';p21:',mat2str(p21),';p22:',mat2str(p22)]);
end

