module HW1 (
    form,
    constGrid,
    flatten,
    access,
    slice,
    vcat,
    hcat,
    without,
    matches2d
) where

-- do not modify the module declaration above!
-- this will ensure that you cannot load (compile)
-- the module without implementing all of the functions.

-- If you have functions you do not want to implement,
-- leave them as undefined or make them have another
-- default value. If you fully remove any of their definitions,
-- that will be a compilation error during evaluation,
-- and you will be eligible for (yay!) a 5 point deduction
-- (that's bad for your grade). Runtime errors in your code 
-- (rather than compilation errors) are acceptable and will simply
-- result in you getting zero from the specific test case causing
-- an error.

-------------------------
-- Fellowship of the Grid (25, 5, 5, 5 points)
form :: [a] -> (Int, Int) -> [[a]] 
form [] (_,_)  = []
form lst (h,w) = [take w lst] ++ (form (drop w lst) (h,w))




constGrid :: a -> (Int, Int) -> [[a]]
constGrid smthng (fst,scnd) = take fst (repeat (take scnd (repeat smthng)))




flatten :: [[a]] -> [a]
flatten [] = [] 
flatten (lst:lsts) = lst ++ (flatten lsts) 



access :: [[a]] -> (Int, Int) -> a
access lst (i,j) = nth j (nth i lst)
nth 0 (lst:lsts) = lst
nth n (lst:lsts) = nth (n-1) lsts


----------------------------
-- The Two Signatures (10, 5, 5, 10 points)
slice :: [[a]] -> (Int, Int) -> (Int, Int) -> [[a]]
slice [] (_,_) (_,_) = []
slice lst (i_1,i_2) (j_1,j_2) =column_helper (row_helper lst (i_1,i_2)) (j_1,j_2)

row_helper lst (frst,scnd) = if frst == 0 
then take scnd lst 
else row_helper (drop 1 lst) (frst-1,scnd-1)

column_helper lst (frst,scnd) = if frst == 0
then map (take scnd ) lst
else column_helper (map (drop 1) lst) (frst-1,scnd-1)



vcat :: [[a]] -> [[a]] -> [[a]]
vcat lst_1 lst_2 = lst_1 ++ lst_2

-- for sequence them vertically we can use *** mapM_ print [1,2,3,4]*** 
hcat :: [[a]] -> [[a]] -> [[a]]
hcat [] [] = []
hcat (hed_1:teyl_1) (hed_2:teyl_2) =([concat ([hed_1] ++ [hed_2])])  ++ (hcat teyl_1 teyl_2)


without :: [[a]] -> (Int, Int) -> (Int, Int) -> [[a]]
without [] (_,_) (_,_) = []
without lst (fsti,scndi) (fstj,scndj) = wout_column_helper (wout_row_helper lst (fsti,scndi)) (fstj,scndj)

wout_row_helper lst (frst,scnd) = take frst lst ++ drop scnd lst
wout_column_helper :: [[a]] -> (Int,Int) -> [[a]]
wout_column_helper [] (_,_)= []
wout_column_helper (lst:lsts) (frst,scnd) = (take frst lst ++ drop scnd lst):(wout_column_helper lsts (frst,scnd))

----------------------------
-- Return of the Non-trivial (30 points, 15 subject to runtime constraints)
matches2d :: Eq a => [[a]] -> [[a]] -> [(Int, Int)]
matches2d  lst pattern =  matches2d_helper lst pattern 0 0 

matches2d_helper lst patrn fst scnd
                        | fst > (length lst) - (length patrn) = []
                        | scnd > (length (lst!!0)- length (patrn!!0)) = matches2d_helper lst patrn (fst+1) 0
                        | otherwise =  if  patrn == slice lst (fst,fst + length patrn) (scnd,scnd + (length (patrn!!0)))
                              then [(fst,scnd)] ++ matches2d_helper lst patrn fst (scnd+1) 
                              else matches2d_helper lst patrn fst (scnd+1)
----------------------------
-- What is undefined? Just a value that will cause an error
-- when evaluated, from the GHC implementation:
-- undefined = error "Prelude.undefined"
-- But it allows your module to be compiled
-- since the function definitions will exist.
