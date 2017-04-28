%% Setup points
clear;

timeSteps  = 15;
iterations = 15; % per timestep 

graphLimits = [ -3 3; -3 3 ];

% matrix of points in the format:
% | p1_x  p1_y |
% | p2_x  p2_y |
% |     ...    |
% | pn_x  pn_y |
points = ...
    [
     -1 1;
     0 1;
     1 1;
     -1 0;
     0 0;
     1 0;
     -1 -1;
     0 -1;
     1 -1
     ];

 numVerts = size( points, 1 );
 
 relations = ...
     [ 
      7 2;
      7 8;
      8 6;
      6 2;
     ];
 
 %% Setup constraints
  
 % marix of distance constraints between 
 % two points where each row represents:
 % | relation1_index  relation2_index  sin cos |
 C_3 = [ 1 2 90; 2 3 90; 3 4 90; 4 1 90 ];
 
 
 
%% Iterate and graph
iterations = 50;

draw;

waitforbuttonpress;
    
for i=1:iterations
    
%     waitforbuttonpress;

    for ri=1:size(C_3,1)
        points = SolveAngleConstraint(                        ...
                                      points,                 ...
                                      relations(C_3(ri,1),:), ...
                                      relations(C_3(ri,2),:), ...
                                      deg2rad  (C_3(ri,3) )   ...  
                                      );
    end
    
    draw;
end


% for ti=1:timeSteps
%     
%     C_1(1,2) = C_1(1,2) + 0.1;
%     C_1(1,3) = C_1(1,3) + 0.2;
%     
%     waitforbuttonpress;
%     
%     for i=1:iterations
%         
%         % adjust for single point constraints
%         for ri=1:size(C_1,1)
%             points(C_1(ri, 1), :) = C_1(ri, 2:3);
%         end
%         
%         % adjust for two point distance constraints
%         for ri=1:size(C_2,1)
%             p1 = points(C_2(ri,1),:);
%             p2 = points(C_2(ri,2),:);
%             dir = p2 - p1;
%             dist = norm( p2 - p1 );
%             diff = dist - C_2(ri,3);
%             dir = dir .* ( 0.5 * diff / dist );
%             points(C_2(ri,1),:) = p1 + dir;
%             points(C_2(ri,2),:) = p2 - dir;
%         end
% 
%         draw;
%     end
% end


waitforbuttonpress;
close all;
