function b = normalize(a)
    b = a / norm(a);
endfunction

function c = cross(a, b)
    x = a(2)*b(3)-a(3)*b(2);
    y = a(3)*b(1)-a(1)*b(3); 
    z = a(1)*b(2)-a(2)*b(1);
    c = [x y z];
endfunction

function R = CreateViewMatrix(_eye, _center, _up)
    disp(_eye);
    disp(_center);
    disp(_up);
    F = _center - _eye;
    _f = normalize(F);
    up = normalize(_up);
    _s = normalize(cross(_f, up));
    u = cross(_s, _f);
    disp(_f, "f")
    disp(_s, "s")
    disp(u, "u")
    M = [_s(1) _s(2) _s(3) 0; u(1) u(2) u(3) 0; -_f(1) -_f(2) -_f(3) 0; 0 0 0 1]
    disp(M)
    T = [1 0 0 -_eye(1); 0 1 0 -_eye(2); 0 0 1 -_eye(3); 0 0 0 1]
    disp(T)
    R = M * T
endfunction


height = 50;
view_point = [0 0 0];
_eye = [0 0 height] + view_point + [0 50 0];
_dir = normalize(view_point - _eye);
up = [0 0 1];

view = CreateViewMatrix(_eye, _eye + _dir, up);

disp(view)

disp(cross([1 2 3], [5 4 3]))
