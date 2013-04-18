//  C - consumption
//  I - investments
//  G - government purchases
//  NX - net exports
function Y = GDP(C, I, G, NX)
    Y = C + I + G + NX
endfunction

//  G - goods
//  S - services
function C = Consumption(G, S)
    C = Goods + Services
endfunction

//  P - matrix of prices
//  Q - matrix of quantities
function G = Goods(P, Q)
    [rows, cols] = size(P)    
    G = 0
    for c = 1 : cols
        G = G + P(1, c) * Q(1, c)
    end
endfunction

//  C - capital equipment
//  I - inventories
//  S - structures
function I = Investment(C, I, S)
    I = C + I + S
endfunction

//  G - goods
//  S - services
function R = GovernmentPurchases(G, S)
    R = G + S
endfunction

//  E - export (domesticaly produced goods)
//  I - import (foreign goods)
function NX = NetExport(E, I)
    NX = E - I
endfunction

function R = GDPDeflator(NGDP, RGDP)
    R = NGDP / RGDP * 100
endfunction

function I = InflationRate(GDPdeflator1, GDPdeflator2)
    I = (GDPdeflator2 - GDPdeflator1) / GDPdeflator1 * 100
endfunction

//  Test 1
Years = [2010, 2011, 2012]
Name = ["Milk", "Honey"]
Prices = [1, 2; 1, 2; 2, 4]
Quantity = [100, 50; 200, 100; 200, 100]

disp(Years', "Years")
disp(Prices, "Prices")
disp(InflationRate(25, 20), "Inflation rate:")
NominalGPD = []
RealGDP = []
DeflatorGDP = []
for year = 1:3
    NominalGDP(year) = Goods(Prices(year,:), Quantity(year,:));
    RealGDP(year) = Goods(Prices(1,:), Quantity(year,:))
    DeflatorGDP(year) = GDPDeflator(NominalGDP(year), RealGDP(year));
    mprintf("Nominal GDP total value in %d is %f\n", Years(year), NominalGDP(year))
    mprintf("Real GDP total value in %d is %f\n", Years(year), RealGDP(year))
    mprintf("GDP deflator for %d year is %f\n", Years(year), DeflatorGDP(year))
    mprintf("Percentage change for nominal GDP in %d year is %f\n", Years(year), GDPDeflator(NominalGDP(year), NominalGDP(1)))
    mprintf("Percentage change for real GDP in %d year is %f\n", Years(year), GDPDeflator(RealGDP(year), RealGDP(1)));        mprintf("Percentage change for GDP deflator in %d year is %f\n\n", Years(year), GDPDeflator(DeflatorGDP(year), DeflatorGDP(1)));
end

