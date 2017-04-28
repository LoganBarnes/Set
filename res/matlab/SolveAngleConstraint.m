function [ points ] = SolveAngleConstraint( points, r1, r2, angle )
%SOLVEANGLECONSTRAINT Summary of this function goes here
%   Detailed explanation goes here

    if angle < 0 || angle > pi
        disp( 'WARNING: angle must be in the range [0,pi]' );
        return;
    end

    optimize = true;
    eps = 1.0e-5;

    p11 = points(r1(1),:);
    p12 = points(r1(2),:);
    p21 = points(r2(1),:);
    p22 = points(r2(2),:);

    % direction vecs
    v1 = p12 - p11;
    v2 = p22 - p21;

    % normalize
    v1 = Normalize( v1 );
    v2 = Normalize( v2 );

    % compute sine and cosine via vector maths
    cosB   = dot( v1, v2 );
    crossB = cross( [v1 0], [v2 0] );
    sinB   = norm( crossB );

    % default cross product for overlapping lines
    if abs(sinB) < eps
        crossB = [0 0 1];
    end

    if r1(1) == r2(1) || r1(1) == r2(2)
        rotPt1 = p11;
        rotPt2 = rotPt1;
    elseif r1(2) == r2(1) || r1(2) == r2(2)
        rotPt1 = p12;
        rotPt2 = rotPt1;
    else
        rotPt1 = ( p11 + p12 ) * 0.5;
        rotPt2 = ( p21 + p22 ) * 0.5;
    end

    normal = Normalize(crossB);

    v11 = [p11 - rotPt1 0];
    v12 = [p12 - rotPt1 0];
    v21 = [p21 - rotPt2 0];
    v22 = [p22 - rotPt2 0];

    if optimize
        sinA = sin(angle);
        cosA = cos(angle);

        sinAMinB = sinA * cosB - sinB * cosA;
        cosAMinB = cosA * cosB + sinA * sinB;

        % using max because floating point error causes 0 to
        % sometimes be a really small negative number
        sinRotAngle = sqrt(max(0,1-cosAMinB)*0.5) * sign( sinAMinB );
        cosRotAngle = sqrt(max(0,1+cosAMinB)*0.5);

        v11 = RotateVectorOptimized(v11,sinRotAngle,cosRotAngle,-normal);
        v12 = RotateVectorOptimized(v12,sinRotAngle,cosRotAngle,-normal);
        v21 = RotateVectorOptimized(v21,sinRotAngle,cosRotAngle, normal);
        v22 = RotateVectorOptimized(v22,sinRotAngle,cosRotAngle, normal);
    else
        angleB = atan2( sinB, cosB );
        rotAngle = (angle-angleB)*0.5;

        v11 = RotateVector(v11,rotAngle,-normal);
        v12 = RotateVector(v12,rotAngle,-normal);
        v21 = RotateVector(v21,rotAngle, normal);
        v22 = RotateVector(v22,rotAngle, normal);
    end

    points(r1(1,1),:) = rotPt1 + v11(1:2);
    points(r1(1,2),:) = rotPt1 + v12(1:2);

    points(r2(1,1),:) = rotPt2 + v21(1:2);
    points(r2(1,2),:) = rotPt2 + v22(1:2);
end

