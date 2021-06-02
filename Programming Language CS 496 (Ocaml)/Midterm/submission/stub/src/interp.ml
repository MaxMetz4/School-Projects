open Ast
open Ds

(* Maxwell Metzner 4/8/21 *)
(* I pledge my honor that I have abided by the Stevens Honor System. *)

let rec apply_proc : exp_val -> exp_val -> exp_val ea_result =
  fun f a ->
  match f with
  |  ProcVal (id,body,env) ->
    return env >>+
    extend_env id a >>+
    eval_expr body
  | _ -> error "apply_proc: Not a procVal"
and
  eval_expr : expr -> exp_val ea_result = fun e ->
  match e with
  | Int(n) -> return (NumVal n)
  | Var(id) -> apply_env id
  | Add(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    return (NumVal (n1+n2))
  | Sub(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    return (NumVal (n1-n2))
  | Mul(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    return (NumVal (n1*n2))
  | Div(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    if n2==0
    then error "Division by zero"
    else return (NumVal (n1/n2))
  | Let(v,def,body) ->
    eval_expr def >>= 
    extend_env v >>+
    eval_expr body 
  | ITE(e1,e2,e3) ->
    eval_expr e1 >>=
    bool_of_boolVal >>= fun b ->
    if b 
    then eval_expr e2
    else eval_expr e3
  | IsZero(e) ->
    eval_expr e >>=
    int_of_numVal >>= fun n ->
    return (BoolVal (n = 0))
  | Pair(e1,e2) ->
    eval_expr e1 >>= fun ev1 ->
    eval_expr e2 >>= fun ev2 ->
    return (PairVal(ev1,ev2))
  | Fst(e) ->
    eval_expr e >>=
    pair_of_pairVal >>= fun p ->
    return (fst p) 
  | Snd(e) ->
    eval_expr e >>=
    pair_of_pairVal >>= fun p ->
    return (snd p)
  | Proc(id,e)  ->
    lookup_env >>= fun en ->
    return (ProcVal(id,e,en))
  | App(e1,e2)  -> 
    eval_expr e1 >>= fun v1 ->
    eval_expr e2 >>= fun v2 ->
    apply_proc v1 v2
  | Letrec(id,par,e1,e2) ->
    extend_env_rec id par e1 >>+
    eval_expr e2

(* ################################################# *)
(* Midterm Functions *)

  | EmptyTable ->
    return @@ TableVal([])

  | Insert(e1,e2,e3) ->
    eval_expr e1 >>= fun v1 ->
    eval_expr e2 >>= fun v2 ->
    eval_expr e3 >>=
    table_of_tableVal >>= fun v3 ->
    (* Was gonna put a match case for procvals but Bonelli said that was a precondition *)
    return @@ TableVal([(v1,v2)] @ v3)

  | Lookup(e1,e2) ->
    eval_expr e1 >>= fun v1 -> 
    eval_expr e2 >>=
    table_of_tableVal >>= fun v2 ->
    let rec search (a : Ds.exp_val) (b : (Ds.exp_val * Ds.exp_val) list) =
      (match b with 
        (* The match is done with list without finding the key: *)
      | [] -> error "Lookup: Key not found."
        (* The match case finds the desired key and returns the value asssociated with it *)
      | (k, v) :: t -> if (k = a) then return @@ v else (search a t))
    in search v1 v2

  | Remove(e1,e2) ->
    eval_expr e1 >>= fun v1 -> 
    eval_expr e2 >>=
    table_of_tableVal >>= fun v2 ->
    let rec search2 (a : Ds.exp_val) (b : (Ds.exp_val * Ds.exp_val) list) =
      (match b with
        (* The match is done with list without finding the key: *)
      | [] -> []
        (* If the desired key is found, omit that key/value from list and move on to the tail *)
      | (k,v) :: t -> if (k = a) then search2 a t else [(k,v)] @ (search2 a t))
    in if (search2 v1 v2 = v2) 
    (* If the result post-remove is same as the input, the key must not exist *)
    then error "Remove: Key not found." 
    else return @@ TableVal(search2 v1 v2)

  | IsEmpty(e) ->
    eval_expr e >>= fun v1 -> 
    return @@ BoolVal(TableVal([]) = v1)
    
  | Size(e) ->
    eval_expr e >>=
    table_of_tableVal >>= fun v1 ->
    (* Unpack the table, then use List.length on it *)
    return @@ NumVal(List.length v1)

(* ################################################# *)

  | Debug(_e) ->
    string_of_env >>= fun str ->
    print_endline str; 
    error "Debug called"
  | _ -> error "Not implemented yet!"

(** [parse s] parses string [s] into an ast *)
let parse (s:string) : expr =
  let lexbuf = Lexing.from_string s in
  let ast = Parser.prog Lexer.read lexbuf in
  ast


(** [interp s] parses [s] and then evaluates it *)
let interp (s:string) : exp_val result =
  let c = s |> parse |> eval_expr
  in run c