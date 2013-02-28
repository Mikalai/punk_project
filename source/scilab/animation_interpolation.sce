//    test 1 for animation position interpolation

frame_start = 1
frame_end = 10

v_start = [0, 0.001353, 0.123324]
v_end = [0.00000, 0, 0]

dv = (v_end - v_start) / (frame_end - frame_start)

i = frame_start:frame_end

for i = frame_start:frame_end
    v = v_start + dv * (i - frame_start)
    disp(v)
end
