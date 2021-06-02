(* Savnick Patel and Maxwell Metzner *)
(* Sample Directed Graph *)

let ex = [(1, 2); (2, 3); (3, 1); (3, 4)]


(*
  1 <---- 3
  |     /\ |
  |    /   | 
 \/  /    \/
  2       4
*)
       
(* 
Eg. outgoing ex 3 => [1,4] 
*)
let rec outgoing_nodes g n =
	match g with 
  | [] -> []
  | h::t -> 
  	if h.hd == n 
    then h.tl.hd::outgoing_nodes(t,n)
    else outgoing_nodes(t,n)
    
(* 
   The list of nodes of the tree without duplicates. The order of the
   nodes in the list is irrelevant.
   eg. nodes ex => [1,2,3,4] 
*)
let rec nodes g =
   match g with 
  | [] -> []
  | h::t -> 
  	if mem h.hd nodes(t)
    then nodes
    else outgoing_nodes(t,n)

(* 
   Remove a node from the graph
   Eg. remove ex 2 =>  [(3, 1); (3, 4)] 
*)
let rec remove g n =
   match g with 
  | [] -> []
  | h::t -> 
  	if h.hd == n || h.tl.hd == n
    then remove(t,n)
    else h::remove(t,n)
  
(* Reachable nodes from a source node. (Extra-credit)
   Eg. reachale ex 3 => [1,4,2,3] 
   *)
let rec reachable g n =
  failwith "implement me"
                               