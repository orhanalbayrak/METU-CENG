module Mini1 (
    gridMap,
    gridMapIf,
    evalExpr,
    getVars,
    evalDeriv,
    parse -- reexported to allow use
    ) where

import Expression
import Parser

-- Do not modify the module declaration and imports above!
-- Also do not change the function signatures and do not
-- remove the dummy implementations of the functions if
-- you want your code to compile.

-- Feel free to import anything else here
import Data.Maybe
import Data.List
import qualified Data.Set as Set

-- gridMap (20 points), map function over grid elements
gridMap :: (a -> b) -> [[a]] -> [[b]]
gridMap _ [] =[]
gridMap (func) (lst:lsts)= [map  func lst] ++ (gridMap func lsts)

-- gridMapIf (20 points), map functions over grid elements 
-- that satisfy the predicate provided as the first arg.
gridMapIf :: (a -> Bool) -> (a -> a) -> [[a]] -> [[a]]
gridMapIf _ _ [] = []
gridMapIf cond func (lst:lsts) = ((gridMapIfHelper cond func lst):[]) ++ (gridMapIf cond func lsts)

gridMapIfHelper:: (a -> Bool) -> (a -> a) -> [a] -> [a]
gridMapIfHelper _ _ [] = []
gridMapIfHelper cond func (lst:lsts) = ((if (cond lst) == True then (func lst) else lst):[]) ++ (gridMapIfHelper cond func lsts)






-- evalExpr (20 points), evaluate the expression by
-- substituting (var, value) pairs given in the first arg.
evalExpr :: [(String, Int)] -> ExprV -> Int


evalExpr [] (Leaf (Constant a)) = a


evalExpr [] (BinaryOperation  Plus (Leaf (Constant a)) (Leaf (Constant b) )) = a + b
evalExpr [] (BinaryOperation  Times (Leaf (Constant a)) (Leaf(Constant b)) ) = a * b
evalExpr [] (UnaryOperation  Minus (Leaf (Constant a))) = (-1)*a
------------------------------------------------------------------------------------------------------------------------------
evalExpr unKnown (BinaryOperation  Plus (Leaf (Constant a)) (Leaf (Constant b) )) = a + b
evalExpr unKnown (BinaryOperation  Times (Leaf (Constant a)) (Leaf(Constant b)) ) = a * b
evalExpr unKnown (UnaryOperation  Minus (Leaf (Constant a))) = (-1)*a
evalExpr unKnown (Leaf (Variable a)) =  (fromJust (lookup a unKnown))
evalExpr unKnown (Leaf (Constant a)) =  a
evalExpr unKnown (BinaryOperation  Plus (Leaf(Variable a)) (Leaf(Constant b)) ) = (fromJust (lookup a unKnown)) + b
evalExpr unKnown (BinaryOperation  Plus (Leaf(Constant a)) (Leaf(Variable b)) ) = a + (fromJust (lookup b unKnown))
evalExpr unKnown (BinaryOperation  Plus (Leaf(Variable a)) (Leaf(Variable b)) ) = (fromJust (lookup a unKnown)) + (fromJust (lookup b unKnown))
evalExpr unKnown (BinaryOperation  Times (Leaf(Variable a)) (Leaf(Constant b)) ) = (fromJust (lookup a unKnown)) * b
evalExpr unKnown (BinaryOperation  Times (Leaf(Constant a)) (Leaf(Variable b)) ) = a * (fromJust (lookup b unKnown))
evalExpr unKnown (BinaryOperation  Times (Leaf(Variable a)) (Leaf(Variable b)) ) = (fromJust (lookup a unKnown)) * (fromJust (lookup b unKnown))
evalExpr unKnown (UnaryOperation  Minus (Leaf (Variable a)) )= (fromJust (lookup a unKnown)) * (-1)
------------------------------------------------------------------------------------------------------------------------------
evalExpr unKnown (BinaryOperation  Plus (Leaf(Constant a)) (smthng)) = a + (evalExpr unKnown smthng)
evalExpr unKnown (BinaryOperation  Plus (Leaf(Variable a)) (smthng)) = (fromJust (lookup a unKnown)) + (evalExpr unKnown smthng)
evalExpr unKnown (BinaryOperation  Plus (smthng) (Leaf(Variable b)) ) = (evalExpr unKnown smthng) + (fromJust (lookup b unKnown))
evalExpr unKnown (BinaryOperation  Plus (smthng) (Leaf(Constant b)) ) = (evalExpr unKnown smthng) + b
evalExpr unKnown (BinaryOperation  Plus (lft) (rigt) ) = (evalExpr unKnown lft) + (evalExpr unKnown rigt)
evalExpr unKnown (BinaryOperation  Times (Leaf(Constant a)) (smthng)) = a * (evalExpr unKnown smthng)
evalExpr unKnown (BinaryOperation  Times (Leaf(Variable a)) (smthng) )= (fromJust (lookup a unKnown)) * (evalExpr unKnown smthng)
evalExpr unKnown (BinaryOperation  Times (smthng) (Leaf(Variable b)) ) = (evalExpr unKnown smthng) * (fromJust (lookup b unKnown))
evalExpr unKnown (BinaryOperation  Times (smthng) (Leaf(Constant b)) ) = (evalExpr unKnown smthng) * b
evalExpr unKnown (BinaryOperation  Times (lft) (rigt) ) = (evalExpr unKnown lft) * (evalExpr unKnown rigt)

evalExpr [] (BinaryOperation Plus (smthng)  (Leaf(Constant a))) = (evalExpr [] smthng) + a
evalExpr [] (BinaryOperation Plus (Leaf(Constant a)) (smthng)) = a + (evalExpr [] smthng)
evalExpr [] (BinaryOperation Times (Leaf(Constant a)) (smthng)) =  a * (evalExpr [] smthng)
evalExpr [] (BinaryOperation Times (smthng)  (Leaf(Constant a))) =  (evalExpr [] smthng) * a
evalExpr [] (UnaryOperation Minus (smthng)) = (-1)*(evalExpr [] smthng)
evalExpr unKnown (BinaryOperation Plus (Leaf(Constant a)) (smthng)) = a + (evalExpr [] smthng)
evalExpr unKnown (BinaryOperation Plus (smthng)  (Leaf(Constant a))) = (evalExpr [] smthng) + a
evalExpr unKnown (BinaryOperation Times (Leaf(Constant a)) (smthng)) =  a * (evalExpr [] smthng)
evalExpr unKnown (BinaryOperation Times (smthng)  (Leaf(Constant a))) =  (evalExpr [] smthng) * a
evalExpr unKnown (UnaryOperation Minus (smthng)) = (-1)*(evalExpr [] smthng)
evalExpr unKnown (UnaryOperation Minus (smthng)) = (-1)*(evalExpr unKnown smthng)

-- getVars (20 points), return the variables contained
-- in the expression in a list (ordered, no duplicates)
unique :: Ord a => [a] -> [a]
unique = Set.toList . Set.fromList
getVars :: ExprV -> [String]
getVars (Leaf (Constant a)) = []
getVars (Leaf (Variable smthng)) = [smthng] 
getVars (BinaryOperation Plus lft rigt) = unique $ getVars lft ++ getVars rigt
getVars (BinaryOperation Times lft rigt) = unique $ getVars lft ++ getVars rigt
getVars (UnaryOperation Minus (smthng)) = unique $ getVars smthng 

-- evalDeriv (20 points), evaluate the first derivative
-- with respect to the variable given in the second
-- arg. using (var, value) pairs given in the first arg.
evalDeriv :: [(String, Int)] -> String -> ExprV -> Int
evalDeriv lst cond  exPVal =    let evalDerivHelper lst cond (Leaf (Constant a)) = 0
                                    evalDerivHelper lst cond (Leaf (Variable smthng)) = if smthng == cond then 1 else 0  
                                    evalDerivHelper lst cond (BinaryOperation Plus lft rigt) = (evalDerivHelper lst cond lft) + (evalDerivHelper lst cond rigt )
                                    evalDerivHelper lst cond (BinaryOperation Times lft rigt) = (evalDerivHelper lst cond lft) * (evalExpr lst  rigt ) +  (evalDerivHelper lst cond rigt)*(evalExpr lst lft) 
                                    evalDerivHelper lst cond (UnaryOperation Minus (smthng)) = (evalDerivHelper lst  cond smthng)*(-1)  
                                 in (evalDerivHelper lst cond exPVal )  


-- Looks like that's all! 
