#include "util.h"
#include "types.h"

int max(int a, int b) {
	if(a > b) return a;
	return b;
}

int maxArgsExpList(A_expList);
int maxArgsExp(A_exp);
int maxArgs(A_stm);

int maxargs(A_stm stm) {
    int l; 
    int r;
	switch(stm->kind) {
		case A_printStm:
			return maxArgsExpList(stm->u.print.exps);
		case A_assignStm:
			return maxArgsExp(stm->u.assign.exp);
		case A_compoundStm:
			l = maxArgs(stm->u.compound.stm1);
			r = maxArgs(stm->u.compound.stm2);
			return max(l, r);
		default:
			return 0;
	}
}

int maxArgs(A_stm stm) {
    int l; 
    int r;
    switch(stm->kind) {
        case A_printStm:
            return maxArgsExpList(stm->u.print.exps);
            break;
        case A_assignStm:
            return maxArgsExp(stm->u.assign.exp);
            break;
        case A_compoundStm:
            l = maxArgs(stm->u.compound.stm1);
            r = maxArgs(stm->u.compound.stm2);
            return max(l, r);
        default:
            return 0;
    }
}

int maxArgsExpList(A_expList expList) {
	if(expList->kind == A_pairExpList) {
		return max(maxArgsExp(expList->u.pair.head), maxArgsExpList(expList->u.pair.tail));
	} 
	if(expList->kind == A_lastExpList) {
		return maxArgsExp(expList->u.last); 
	}
}

int maxArgsExp(A_exp exp) {
	switch(exp->kind) {
		case A_idExp:
            return 1;
		case A_numExp:
			return 1;
		case A_opExp:
			return max(maxArgsExp(exp->u.op.left), maxArgsExp(exp->u.op.right));
		case A_eseqExp:
			return max(maxArgs(exp->u.eseq.stm), maxArgsExp(exp->u.eseq.exp));
	}
}

int main() {
	
	A_stm prog =
		A_CompoundStm(A_AssignStm("a",
			A_OpExp(A_NumExp(5), A_plus, A_NumExp(3))),
		A_CompoundStm(A_AssignStm("b",
			A_EseqExp(A_PrintStm(A_PairExpList(A_IdExp("a"),
				A_LastExpList(A_OpExp(A_IdExp("a"), A_minus, A_NumExp(1))))),
		A_OpExp(A_NumExp(10), A_times, A_IdExp("a")))),
			A_PrintStm(A_LastExpList(A_IdExp("b")))));
	
	A_stm onePrint = A_PrintStm(A_LastExpList(A_IdExp("a")));
	A_stm twoPrint = A_PrintStm(
						A_PairExpList(A_IdExp("b"), A_LastExpList(
														A_IdExp("c"))));

	int args = maxargs(prog);
    printf("%d\n", args);
	return 0;
}
