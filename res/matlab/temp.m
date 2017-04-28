clear;
% 
% for a=0:15:360
%     angle = deg2rad(a);
%     sinAh = sin(angle*0.5);
%     cosA = cos(angle);
%    disp(['(',num2str(a/2),') sinAh: ',num2str(sinAh),'-> ',num2str(sqrt((1-cosA)*0.5))]); 
% end


for a=0:15:360
    angle = deg2rad(a);
    cosAh = cos(angle*0.5);
    cosA = cos(angle);
   disp(['(',num2str(a/2),') cosA: ',num2str(cosA),' -- cosAh: ',num2str(cosAh),'-> ',num2str(sqrt((1+cosA)*0.5))]); 
end