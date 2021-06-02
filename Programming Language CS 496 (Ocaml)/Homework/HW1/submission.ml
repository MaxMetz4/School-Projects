(* Maxwell Metzner HW1-A Bonelli Section A*)
(* I pledge my honor that I have abided by the Stevens Honor System. *)
(* ******************************************** *)
(** Basic functions on finite automata *)
(* ******************************************** *)
(**
   Code stub for assignment 1
*)

type symbol = char
type input = char list

type state = string
  
(* transition function *)
type tf = (state * symbol * state) list
    
let get1 (x,_,_) = x;;
let get2 (_,x,_) = x;;
let get3 (_,_,x) = x;;

(* initial state * transition function * end state *)
type fa = { states: state list; start:state; tf: tf; final: state list} 

(* ******************************************** *)
(* Examples of automata *)
(* ******************************************** *)

(**Tests a regular working automata *)
let a = {states = ["q0";"q1";"q2"];
         start = "q0";
         tf = [("q0",'a',"q1"); ("q1",'b',"q1"); ("q1",'c',"q2")];
         final = ["q2"]}

(**Tests dead states *)
let a2 = {states = ["q0";"q1";"q2";"q3";"q4"];
          start = "q0";
          tf = [("q0",'a',"q1"); ("q1",'b',"q1")
               ; ("q1",'c',"q2");  ("q3",'a',"q4")];
          final= ["q2"]
         }

(**Tests deterministic *)
let b = {states = ["q0";"q1";"q2";"q3";"q4"];
          start = "q0";
          tf = [("q0",'a',"q1"); ("q0",'a',"q2"); ("q1",'b',"q1")
               ; ("q1",'c',"q2");  ("q3",'a',"q4")];
          final= ["q2"]
         }

(**Tests unreachable *)
let c = {states = ["q0";"q1";"q2"];
         start = "q0";
         tf = [("q1",'b',"q1"); ("q1",'c',"q2")];
         final = ["q2"]}


let tf_of_a = [("q0",'a',"q1"); ("q1",'b',"q1"); ("q1",'c',"q2")]



(* ******************************************** *)
(* Helper functions *)
(* ******************************************** *)

let input_of_string s =
  let rec exp i l =
    if i < 0 then l else exp (i - 1) (s.[i] :: l) in
  exp (String.length s - 1) []

(**For some reason Option.get wasnt working so this is my version of that *)
let content x = 
  match x with
    Some c -> c
  | None -> ""

let rec apply_helper f st sym =
  match f with
    [] -> None
  | (x,y,z) :: t ->  if ((x = st) && (y = sym)) then Some z else apply_helper (List.tl f) st sym

(**Needs f.tf for f *)
let rec next tf st = 
  match tf with
  [] -> []
  | (x,y,z) :: t -> if x = st then y :: next t st else next t st

(**adapted for reachable to take out self transitions *)
let rec next2 tf st = 
  match tf with
  [] -> []
  | (x,y,z) :: t -> if (x = st) && (x <> z) then z :: next2 t st else next2 t st

(**Gives a boolean if there are duplicates or not *)
let rec duplicates list =
  match list with
    [] -> false
  | h :: t -> let x = (List.filter (fun x -> x = h) t) in if x = [] then duplicates t else true

(**Intended to work with start, finding the specified state *)
let rec search st list = 
  match list with
  [] -> false
  | h :: t -> if h = st then true else search st t

(**Like search but takes in a list instead of a single state so it works with final *)
let rec searches st list =
  match list with 
  [] -> true
  | h :: t -> if (search h list) = false then false else searches st t

let rec reachable_helper st tf = 
  match tf with
  [] -> []
  | (x,y,z) :: t -> if x = st then z :: reachable_helper st t else reachable_helper st t

(**Returns transitions list that are not taken *)
let rec dead_state_helper st tf =
  match tf with 
  [] -> []
  | (x,y,z) :: t -> if x = st then dead_state_helper z t else (x,y,z) :: dead_state_helper x t
(* ******************************************** *)
(* Simulating automata *)
(* ******************************************** *) 

(* f=the machine, st=state, sym=transition name *)
(*Cycles through 3-tuple of the automata transitions, making sure current state and transition name match *)
let apply_transition_function f st sym =
  apply_helper f.tf st sym

(**f=automata, st=current state, input=string of transformations *)
let rec accept_helper f st input =
  match input with
    [] -> true
  | _ ->  if (apply_transition_function f st (List.hd input) <> None) 
            then accept_helper f (content (apply_transition_function f st (List.hd input))) (List.tl input)
              else false

let accept f input =
  accept_helper f f.start input

(**fa=automata, st=current state, list=list of characters that go out of current state, collected by next *)
(**This would be in helper section but it requires apply_transition_function *)
let rec deterministic_helper fa st list=
  match list with
    [] -> true
  | h :: t -> if (duplicates list = true) then false else deterministic_helper fa (content (apply_transition_function fa st h)) t

let deterministic fa =
  deterministic_helper fa fa.start (next fa.tf fa.start)

(**Checks for existence of start & end states, runs automata through determinism checker *)
let valid fa =
  if (search fa.start fa.states) && (searches fa.final fa.states) && (deterministic fa = true) then true else false

(**does the selected state have a path back to the start state *)
let rec trace_back f tf start state =
  match tf with
  [] -> false
  (**The next line is what has the error *)
  | (x,y,z) :: t -> if ((x=start) && (z=state) || (state=start)) then true else if (x <> z) && (state = z) then trace_back f tf start x else trace_back f t start state

let rec helper1 f states =
  match states with
  [] -> []
  | h :: t -> if ((trace_back f (List.rev f.tf) f.start h = true) || (trace_back f f.tf f.start h = true)) then h :: (helper1 f t) else (helper1 f t)

let reachable fa =
  (List.rev (helper1 fa (List.rev fa.states)))

(**False means its not supposed to be there *)
let rec checker list state =
  match list with
  [] -> false
  | h :: t -> if h = state then true else checker t state

let rec transition_checker transitions states = 
  match transitions with
  [] -> []
  | (x,y,z) :: t -> if (checker states x) = false || (checker states z) = false then transition_checker t states else (x,y,z) :: transition_checker t states

let rec final_checker list states = 
  match list with
  [] -> []
  | h :: t -> if (checker states h) = false then final_checker t states else h :: final_checker t states

let remove_dead_states fa = 
  { 
    states = reachable fa;
    start = fa.start;
    tf = transition_checker (fa.tf) (reachable fa);
    final = final_checker fa.final (reachable fa)
  }