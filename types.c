#include "util.h"

typedef char * string;
typedef struct A_stm_ * A_stm;
typedef struct A_exp_ * A_exp;
typedef struct A_expList_ * A_expList;
typedef enum {A_plus, A_minus, A_times, A_div} A_binop;

struct A_stm_ {	enum {A_compoundStm, A_assignStm, A_printStm} kind;
				union {	struct {A_stm stm1, stm2; } compound;
						struct {string id; A_exp exp;} assign;
						struct {A_expList exps; } print;
					} u;
			};

/*	Constructors for a statement
	Statements can either be 
	- compound statements
	- assignment statements ie. string and identifier
	- a list of expressions
*/

A_stm A_CompoundStm(A_stm stm1, A_stm stm2) {
	A_stm s = checked_malloc(sizeof(*s));
	s->kind = A_compoundStm;
	s->u.compound.stm1 = stm1;
	s->u.compound.stm2 = stm2;
	return s;
}

A_stm A_AssignStm(string id, A_exp exp) {
	A_stm s = checked_malloc(sizeof(*s));
	s->kind = A_assignStm;
	s->u.assign.id = id; 
	s->u.assign.exp = exp;
	return s;
}

A_stm A_PrintStm(A_expList exps) {
	A_stm s = checked_malloc(sizeof(*s));
	s->kind = A_printStm;
	s->u.print.exps = exps;
	return s;
}

struct A_exp_ {	enum {A_idExp, A_numExp, A_opExp, A_eseqExp } kind;
				union {	string id;
						int num;
						struct {A_exp left; A_binop oper; A_exp right; } op;
						struct {A_stm stm; A_exp exp; } eseq;
				} u;
			};

/* 	Constructors for an expression
	Expressions can either be:
	- an identifier
	- a number (int, float, etc)
	- two sets of expressions separated by a binary operator
	- an expression sequence, in the form of (s, e)
	... which evaluates the statement S for side effects before evaluating
	... and returning the result of the expression e
*/

A_exp A_IdExp(string id) {
	A_exp e = checked_malloc(sizeof(*e));
	e->kind = A_idExp;
	e->u.id = id;
	return e;
}

A_exp A_NumExp(int num) {
	A_exp e = checked_malloc(sizeof(*e));
	e->kind = A_numExp;
	e->u.num = num;
	return e;
}

A_exp A_OpExp(A_exp left, A_binop oper, A_exp right) {
	A_exp e = checked_malloc(sizeof(*e));
	e->kind = A_opExp;
	e->u.op.left = left;
	e->u.op.oper = oper;
	e->u.op.right = right;
	return e;
}

A_exp A_EseqExp(A_stm stm, A_exp exp) {
	A_exp e = checked_malloc(sizeof(*e));
	e->kind = A_eseqExp;
	e->u.eseq.stm = stm;
	e->u.eseq.exp = exp;
	return e;	
}

struct A_expList_ {	enum {A_pairExpList, A_lastExpList} kind;
					union {	struct {A_exp head; A_expList tail;} pair;
							A_exp last;
						} u;
			};

/*	Constructors for an expression list 
	An expression list is a list of expressions, but taking the form of a
	... expression (the head) and an expression list (the tail).
	Note that an expression can include further statements, ie A_esqeExp (stm, exp)
*/

A_expList A_PairExpList(A_exp head, A_expList tail) {
	A_expList l = checked_malloc(sizeof(*l));
	l->kind = A_pairExpList;
	l->u.pair.head = head;
	l->u.pair.tail = tail;
	return l;
}

A_expList A_LastExpList(A_exp exp) {
	A_expList l = checked_malloc(sizeof(*l));
	l->kind = A_lastExpList;
	l->u.last = exp;
	return l;
}

