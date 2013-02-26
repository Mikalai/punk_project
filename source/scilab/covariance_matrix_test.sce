//    TEST 1
p1 = [-1, -2, 1];
p2 = [1,0,2];
p3 = [2,-1,3];
p4 = [2,-1,2];

p = [p1; p2; p3; p4];

res = mvvacov(p)

disp(res, "Test 1: ")

//    TEST 2
p1 = [0,0,0]

p = [p1]

res = mvvacov(p)

disp(res, "Test 2: ")

//    TEST 3
p1 = [0,0,0]
p2 = [1,0,0]

p = [p1; p2]

res = mvvacov(p)

disp(res, "Test 3: ")


//    TEST 4
p1 = [1,0,0]
p2 = [1,0,0]

p = [p1; p2]

res = mvvacov(p)

disp(res, "Test 4: ")

//    TEST 5
p1 = [0,1,0]
p2 = [1,0,0]

p = [p1; p2]

res = mvvacov(p)

disp(res, "Test 5: ")

//    TEST 6
p1 = [0,1,0]
p2 = [1,0,0]
p3 = [0,0,1]

p = [p1; p2; p3]

res = mvvacov(p)

disp(res, "Test 6: ")

//    TEST 7
p1 = [-1,-1,-1]
p2 = [-1,-1,1]
p3 = [-1,1,-1]
p4 = [-1,1,1]
p5 = [1,-1,-1]
p6 = [1,-1,1]
p7 = [1,1,-1]
p8 = [1,1,1]

p = [p1; p2; p3; p4; p5; p6; p7; p8]

res = mvvacov(p)

disp(res, "Test 7: ")
