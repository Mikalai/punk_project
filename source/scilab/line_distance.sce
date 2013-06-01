function [flag, t1, t2, dst] = CrossLineLine(line1, line2)
//CrossLineLine Calculates intersection of 2 lines
//  line returns, or several flags
//  flag = 1 - No intersection
//   flag = 0 - Intersection
    s1 = line1(1)
    v1 = line1(2) - line1(1)
    s2 = line2(1)
    v2 = line2(2) - line2(1)
    
    m = [v1'*v1 -v1'*v2; v1'*v2 -v2'*v2];
    b = [(s2 - s1)' * v1; (s2 - s1)' * v2];
    
    d = det(m);
    
    if (abs(d) < 1e-5) then
        flag = 1;
        return        
    end
    
    res = inv(m) * b;
    
    t1 = res(1);
    t2 = res(2);
    
    p1 = s1 + t1 * v1;
    p2 = s2 + t2 * v2;
    
    dst = norm(p1 - p2);
    flag = 0
    
    
