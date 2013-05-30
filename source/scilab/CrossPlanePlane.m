function [line, flag] = CrossPlanePlane(a, b)
%CROSS_PLANE_PLANE Calculates intersection of 2 planes
%   line returns, or several flags
%   flag = 1 - No intersection
%   flag = 0 - Intersection

    n1 = [ a(1); a(2); a(3) ];
    n2 = [ b(1); b(2); b(3) ];   
    n3 = cross(n1, n2);
    n3 = n3 / norm(n3);
    
    c = [n3(1); n3(2); n3(3); 0];
    
    m = [ n1(1) n1(2) n1(3); n2(1) n2(2) n2(3); n3(1) n3(2) n3(3) ];
    
    d = det(m);
    
    if (abs(d) < 0.0001)
        flag = 1;
        return
    end
    
    p = [-a(4); -b(4); 0];
    org = inv(m) * p;
    
    line = {org n3};
    flag = 0;

    