%% Setup points
clear;

timeSteps  = 10;
iterations = 15; % per timestep 

graphLimits = [ -3 3; -3 3 ];

% matrix of points in the format:
% | p1_x  p1_y |
% | p2_x  p2_y |
% |     ...    |
% | pn_x  pn_y |
points = ...
    [
     0 0;
     1 0;
     2 0;
     -1 0;
     -2 0;
     ];

 numVerts = size( points, 1 );
 
 relations = ...
     [ 
      2 1;
      2 3;
      4 1;
      4 5
     ];
 
 %% Setup constraints
 
 % matrix of constraints on a single point
 % where each row represents:
 % | point_index  constraint_on_x  constraint_on_y |
 C_1 = [ 1 0.0 0.0 ];
 
 % marix of distance constraints between 
 % two points where each row represents:
 % | point1_index  point2_index  distance |
 C_2 = [ 1 2 1; 1 4 1.5; 4 5 0.5; 2 3 0.25 ];
 
 % marix of angle constraints between 
 % two relations where each row represents:
 % | relation1_index  relation2_index  angleDegrees |
 C_3 = [ 1 2 90; 3 4 40; 1 3 75 ];
 
 
 
%% Iterate and graph

draw;

for ti=1:timeSteps
    
    C_1(1,2) = C_1(1,2) + 0.1;
    C_1(1,3) = C_1(1,3) + 0.2;
    
    waitforbuttonpress;
    
    for i=1:iterations
        
        % adjust for single point constraints
        for ri=1:size(C_1,1)
            points(C_1(ri, 1), :) = C_1(ri, 2:3);
        end
        
        % adjust for two point distance constraints
        for ri=1:size(C_2,1)
            p1 = points(C_2(ri,1),:);
            p2 = points(C_2(ri,2),:);
            [p1,p2] = SolveDistanceConstraint(p1, p2, C_2(ri,3));
            points(C_2(ri,1),:) = p1;
            points(C_2(ri,2),:) = p2;
        end

        % adjust for two relation angle constraints
        for ri=1:size(C_3,1)
            points = SolveAngleConstraint(                        ...
                                          points,                 ...
                                          relations(C_3(ri,1),:), ...
                                          relations(C_3(ri,2),:), ...
                                          deg2rad( C_3(ri,3) )    ...  
                                          );
        end
        
        draw
    end

end


waitforbuttonpress;
close all;
