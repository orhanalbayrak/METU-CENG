:- module(hw, [cost/2, sort_units/2, buyable/4]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE
cost([],0).
cost([active_unit(Champ,Star)|Rem], Cost) :- unit(Champ, TempCost, _),
                                     
                                     cost(Rem,Result),
                                     Cost is Result + TempCost*3**(Star-1).


insert(Chmp, [], [Chmp]).
insert(Chmp, [Chmp2|LftLst], [Chmp, Chmp2|LftLst]):- cost([active_unit(Chmp,1)], Cost1),
                      cost([active_unit(Chmp2,1)], Cost2), Cost1 >= Cost2, !.
                       
insert(Chmp, [Chmp2|LftLst], [Chmp2|LftLst2]):- insert(Chmp, LftLst, LftLst2).

                                     
sort_units([], []).
sort_units([Chmp|LftLst], TmpRes):- sort_units(LftLst, TmpRes1), insert(Chmp, TmpRes1, TmpRes).



combin([],[]).

combin([_|Val],Val2) :- combin(Val,Val2).
combin([Othr|Val],[Othr|Val2]) :- combin(Val,Val2).


cal([],0).
cal([CombsChamp|RemIt],Calculated) :- cost([active_unit(CombsChamp,1)], Cost),
                                    cal(RemIt,TempC),
                                    Calculated is TempC + Cost.
                                    
%buyable([Units], Money, [Bought Units], RemainingMoney).
buyable(_,0,[],0).
buyable(Champs, Money, BoughtChamps, RemainingMoney) :- combin(Champs,CombsChamps),
                                                  cal(CombsChamps,Calculated),
                                                  Money < Calculated, !.
buyable(Champs, Money, BoughtChamps, RemainingMoney) :- 
                                                combin(Champs,CombsChamps),
                                                cal(CombsChamps,Calculated),
                                                Money >= Calculated,
                                                RemainingMoney is Money - Calculated,
                                                BoughtChamps = CombsChamps.
                                                  