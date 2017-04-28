scatter(points(:,1), points(:,2));
hold on;
for ri=1:size(relations,1)
    plot(points(relations(ri,:),1),points(relations(ri,:),2));
end
xlim(graphLimits(1,:));
ylim(graphLimits(2,:));
hold off;
drawnow;
