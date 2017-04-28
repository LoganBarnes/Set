function [ sine, cosine, tangent ] = GetAngle2( v1, v2 )
%GETANGLE Summary of this function goes here
%   Detailed explanation goes here

    v1 = v1 / norm( v1 );
    v2 = v2 / norm( v2 );
    sine = dot( v1, v2 );
    
    v1 = [v1 0];
    v2 = [v2 0];
    cosine = norm( cross( v1, v2 ) );

    disp([num2str(sine),', ',num2str(cosine)]);
end

