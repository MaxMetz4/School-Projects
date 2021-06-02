(* Maxwell Metzner *)
(* I pledge my honor that I have abided by the Stevens Honor System. *)

open Ast
open Ds

(* params * body * super * fields *)
type method_decl = string list*Ast.expr*string*string list

type method_env = (string*method_decl) list

type class_decl = string*string list*method_env

type class_env = ((string*class_decl) list)
                 
(* Global holding the store *)
let g_store = Store.empty_store 20 (NumVal 0)

(* Global holding class declarations *)
let g_class_env : class_env ref = ref []


(* Helper functions for SOOL *)
    
(* 
 * Return all visible fields from class c_name 
 * Note: Should produce an error if the super class does not exist, this is pending  
*)
let rec get_fields cs c_name class_decls =
  match class_decls with
  | [] -> []
  | Class (name,super,fields,_methods)::_ when name=c_name ->
       fields :: get_fields cs super cs
  | Class (_,_,_,_)::cs' -> get_fields cs c_name cs'

(* 
 * Return all visible methods from class c_name 
 * Note: Should produce an error if the super class does not exist, this is pending  
*)
let rec get_methods cs c_name fss = function
  | [] -> []
  | Class (name,super,_fields,methods)::_ when name=c_name ->
    (List.map (fun (Method(n,pars,body))
               -> (n,(pars,body,super,List.flatten fss)))
methods) @ get_methods cs super (List.tl fss) cs
  | Class (_,_,_,_)::cs' -> get_methods cs c_name fss cs'
                                                
(* 
 * Initialize contents of g_class_env variable 
*)
let initialize_class_env cs = 
  let rec initialize_class_env' cs = function
    | [] -> ()
    | Class (name,super,fields,methods)::cs' ->
      let fss = fields :: get_fields cs super cs
      in let ms = (List.map (fun (Method(n,pars,body))
                              -> (n,(pars,body,super,List.flatten fss)))
                     methods) @ get_methods cs super (List.tl fss) cs
      in
      g_class_env := (name,(super,List.flatten fss,ms))::!g_class_env;
      initialize_class_env' cs cs'
  in g_class_env := [];
     initialize_class_env' cs cs

let lookup_class : string -> class_env -> class_decl ea_result  = fun c_name c_env ->
  (* searches for the class c_name in the class environment c_env *)
  let rec iterator c_name2 c_env2 = 
  (match c_env2 with
  (* return an error if the class does not exist *)
  | [] -> error "lookup_class: class c_name not found"
  (* return a class_decl if it does. *)
  | (str, decl) :: t -> 
    if (str=c_name2) then return @@ decl 
    else iterator c_name2 t)
  in
  (iterator c_name c_env)
    
let rec new_env : string list -> env ea_result  = fun fs ->
  (* creates the environment and also allocates a dummy value for all the entries in the store. *)
  (match fs with
  | [] -> return EmptyEnv
  | h :: [] -> 
  (extend_env h (RefVal (Store.new_ref g_store (NumVal 0))))
  | h :: tl -> 
  extend_env h (RefVal (Store.new_ref g_store (NumVal 0))) >>+ new_env tl)
 
let slice fs env =
  let rec slice' fs acc env =
    match fs, env with
    | [],_ -> acc
    | id::ids, ExtendEnv(id',ev,tail) when id=id' ->
      slice' ids (ExtendEnv(id',ev,acc)) tail
    | _,_ -> failwith "slice: ids different or lists have different lengths"
  in
  return (slice' (List.rev fs) EmptyEnv env)
    
let lookup_method : string -> string -> class_env ->
  method_decl option = fun c_name m_name c_env ->
  (* find class decl in class_env, then take the method_env of the decl and find the method_decl *)
  let rec find_c : string -> class_env -> method_env = fun class_name class_environment -> 
  (match class_environment with
  | [] -> failwith "class not found in c_env"
  | (str,(_,_,m_env)) :: tl -> if (str = class_name) then m_env else (find_c  class_name tl)) in
  let rec find_m : string -> method_env -> method_decl option = fun method_name method_environment ->
  (match method_environment with
  | [] -> None
  | (str2, decl2) :: tl2 -> if (method_name = str2) then Some decl2 else (find_m method_name tl2)) in 
  find_m m_name (find_c c_name c_env)

(* Helper function for records *)
let rec addIds fs evs =
  match fs,evs with
  | [],[] -> []
  | (id,_)::t1, v::t2 -> (id,v):: addIds t1 t2
  | _,_ -> failwith "error: lists have different sizes"

let rec apply_method : string -> exp_val -> exp_val list ->
  method_decl -> exp_val ea_result = fun m_name self args (pars,body,super,fs) -> 
  let l = Store.new_ref g_store self
  and l_args = List.map (fun ev -> RefVal (Store.new_ref g_store ev)) args
  in let l' = Store.new_ref g_store (StringVal super)
  in
  if List.length args<> List.length pars
  then error (m_name ^": args and params have different lengths")
  else
  obj_of_objectVal self >>= fun  (_c_name,env) ->
  slice fs env >>+
  extend_env_list ("_super"::"_self"::pars) ((RefVal l')
                                                ::(RefVal l)::l_args) >>+
  eval_expr body 
and
  apply_proc ev1 ev2 =
  match ev1 with
  | ProcVal(par,body,en) ->
    return en >>+
    extend_env par (RefVal (Store.new_ref g_store ev2)) >>+
    eval_expr body
  | _ -> error "apply_proc: Not a procVal"
and
  eval_expr : expr -> exp_val ea_result = fun e ->
  match e with
  | Int(n) -> return @@ NumVal n
  | Var(id) -> 
    apply_env id >>=
    int_of_refVal >>= fun l ->
    Store.deref g_store l >>= fun ev ->
    return ev
  | Add(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    return @@ NumVal (n1+n2)
  | Sub(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    return @@ NumVal (n1-n2)
  | Mul(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    return @@ NumVal (n1*n2)
  | Div(e1,e2) ->
    eval_expr e1 >>=
    int_of_numVal >>= fun n1 ->
    eval_expr e2 >>=
    int_of_numVal >>= fun n2 ->
    if n2==0
    then error "Division by zero"
    else return @@ NumVal (n1/n2)
  | Let(v,def,body) ->
    eval_expr def >>= fun ev ->
    let l = Store.new_ref g_store ev
    in extend_env v (RefVal l) >>+
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
    return @@ BoolVal (n = 0)
  | Pair(e1,e2) ->
    eval_expr e1 >>= fun ev1 ->
    eval_expr e2 >>= fun ev2 ->
    return @@ PairVal(ev1,ev2)
  | Fst(e) ->
    eval_expr e >>=
    pair_of_pairVal >>= fun p ->
    return @@ fst p
  | Snd(e) ->
    eval_expr e >>=
    pair_of_pairVal >>= fun p ->
    return @@ snd p
  | Proc(id,e)  ->
    lookup_env >>= fun en ->
    return (ProcVal(id,e,en))
  | App(e1,e2)  ->
    eval_expr e1 >>= fun v1 ->
    eval_expr e2 >>= fun v2 ->
    apply_proc v1 v2
  | Letrec(id,par,e,target) ->
    let l = Store.new_ref g_store UnitVal in
    extend_env id (RefVal l) >>+
    (lookup_env >>= fun env ->
     Store.set_ref g_store l (ProcVal(par,e,env)) >>= fun _ ->
     eval_expr target
    )
  (* Mutable references operations *)
  | Set(id,e) ->
    eval_expr e >>= fun ev ->
    apply_env id >>=
    int_of_refVal >>= fun l ->
    Store.set_ref g_store l ev >>= fun _ ->
    return UnitVal
  | BeginEnd([]) ->
    return UnitVal
  | BeginEnd(es) ->
    sequence (List.map eval_expr es) >>= fun vs ->
    return (List.hd (List.rev vs))
  (* Record operations *)
  | Record(fs) ->
    sequence (List.map (fun (_, e) -> eval_expr e) fs) >>= fun evs ->
    return (RecordVal (addIds fs evs))
  | Proj(e,id) ->
    eval_expr e >>=
    fields_of_recordVal >>= fun fs ->
    (match List.assoc_opt id fs with
    | None -> error "not found"
    | Some ev -> return ev)
    
  (* SOOL operations *)
  | NewObject(c_name,es) ->
    (* 1. Evaluate the arguments es producing a list of expressed values args. *)
    sequence (List.map eval_expr es) >>= fun args ->
    (* 2. Lookup the class c_name in the class environment held in g_class_env. *)
    lookup_class c_name !g_class_env >>= fun (_super, fields, methods) -> 
    (* 3. Create an environment for the newly created object using fields *)
    new_env fields >>= fun env -> 
    let self = ObjectVal(c_name,env) in
    (* 4. Initialize method should be called. *)
    let m = List.assoc_opt "initialize" methods in
    if (m = None) 
      (* If None is returned, return ObjectVal(c_name,env). *)
    then return self
      (* If it is found, call it then return ObjectVal(c_name,env) *)
    else (apply_method "initialize" self args (Option.get m) >>= fun _ ->
    return self) 
  | Send(e,m_name,es) ->
    (* 1. Evaluate e and make sure it is an object, *)
    eval_expr e >>= fun self ->
    let c_name = (match self with
    | ObjectVal(temp,_) -> temp
    | _ -> failwith "e is not an ObjectVal") in
    (* 2. Evaluate the arguments es producing a list of expressed values args. *)
    sequence (List.map eval_expr es) >>= fun args ->
    (* 3. Look for and apply the method m_name. *)
    (match lookup_method c_name m_name ! g_class_env with
    | None -> error "Method not found"
    | Some m -> apply_method m_name self args m)
  | Self ->
    eval_expr (Var "_self")
  | Super(m_name,es) ->
    (* 1. Evaluate es to expressed values args. Pass on to method m_name *)
    sequence (List.map eval_expr es) >>= fun args ->
    (* 2. Lookup who the super class is in the current environment and is a string. *)
    (* !!! THIS LINE GIVES "Error ( _super  not found!)" !!! *)
    eval_expr (Var "_super") >>= 
    string_of_stringVal >>= fun c_name ->
    (* 3. Lookup who self is in the current environment. *)
    eval_expr (Var "_self") >>= fun self ->
    (* 4. lookup the method m_name and then apply it using apply_method *)
    (match lookup_method c_name m_name ! g_class_env with
      | None -> error " Method not found "
      | Some m -> apply_method m_name self args m)
      
  (* List operations* *)
  | List(es) ->
    sequence (List.map eval_expr es) >>= fun args ->
    return (ListVal args)
  | Cons(e1,e2) ->
    eval_expr e1 >>= fun ev ->
    eval_expr e2 >>=
    list_of_listVal >>= fun l ->
    return (ListVal (ev::l))
  | Hd(e) ->
    eval_expr e >>=
    list_of_listVal >>= fun l ->
    return (List.hd l)
  | Tl(e) ->
    eval_expr e >>=
    list_of_listVal >>= fun l ->
    return (ListVal (List.tl l))
  | EmptyPred(e) ->
    eval_expr e >>=
    list_of_listVal >>= fun l ->
    return (BoolVal (l=[]))
  (* Debug *)
  | Debug(_e) ->
    string_of_env >>= fun str_env ->
    let str_store = Store.string_of_store string_of_expval g_store
    in (print_endline (str_env^"\n"^str_store);
    error "Reached breakpoint")
  | _ -> error ("eval_expr: Not implemented: "^string_of_expr e)
and
  eval_prog : prog -> exp_val ea_result = fun (AProg(cs, e)) ->
    initialize_class_env cs;   (* Step 1 *) 
    eval_expr e                (* Step 2 *)


(* Parse a string into an ast *)

let parse s =
  let lexbuf = Lexing.from_string s in
  let ast = Parser.prog Lexer.read lexbuf in
  ast

let lexer s =
  let lexbuf = Lexing.from_string s
  in Lexer.read lexbuf


(* Interpret an expression *)
let interp (s:string) : exp_val result =
  let c = s |> parse |> eval_prog
  in run c

let read_file (filename:string) : string = 
  let lines = ref [] in
  let chan = open_in filename in
  try
    while true do
      lines := input_line chan :: !lines
    done;
    "" (* never reaches this line *)
  with End_of_file ->
    close_in chan;
    String.concat "" (List.rev !lines)

(* Interpret an expression read from a file with optional extension .rec *)
let interpf (s:string) : exp_val result = 
  let s = String.trim s      (* remove leading and trailing spaces *)
  in let file_name =    (* allow rec to be optional *)
       match String.index_opt s '.' with None -> s^".sool" | _ -> s
  in
  interp @@ read_file file_name

let interpp () : exp_val result = 
  interpf "ex1"


let parsef (s:string) : Ast.prog = 
  let s = String.trim s      (* remove leading and trailing spaces *)
  in let file_name =    (* allow rec to be optional *)
       match String.index_opt s '.' with None -> s^".sool" | _ -> s
  in
  parse @@ read_file file_name
