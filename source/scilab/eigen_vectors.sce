//    TEST 1
p = [3/2, 1/2, 3/4;
     1/2, 1/2, 1/4;
     3/4, 1/4, 1/2]
     
res = gsort(spec(p))

disp(res, "Test 1: ")

//    TEST 2
p = [1, 0, 0;
     0, 1, 0;
     0, 0, 1]
     
res = gsort(spec(p))

disp(res, "Test 2: ")