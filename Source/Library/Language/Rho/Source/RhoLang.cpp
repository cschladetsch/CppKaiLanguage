#include "KAI/Language/Rho/RhoLang.h"

#include <KAI/Core/File.h>

#include <fstream>
#include <iostream>

#include "KAI/Executor/Executor.h"

using namespace std;

KAI_BEGIN

void RhoLang::Print() const {
    cout << "Input:" << endl;
    KAI_TRACE_1(lex_->GetInput());

    cout << "Lexer:" << endl;
    KAI_TRACE_1(lex_->ToString());

    cout << "Parser:" << endl;
    KAI_TRACE_1(parse_->ToString());

    cout << "Trans:" << endl;
    KAI_TRACE_1(trans_->ToString());
}

Pointer<Continuation> RhoLang::TranslateFile(const char *name, Structure st) {
    return Translate(File::ReadAllText(name).c_str(), st);
}

Pointer<Continuation> RhoLang::Translate(const char *text, Structure st) {
    if (lex_->failed) return Fail(lex_->error), Object();

    if (parse_->failed) return Fail(parse_->GetError()), Object();

    auto trans = make_shared<Translator>(reg_);
    auto cont = trans->Translate(text, st);
    if (trans->failed) return Fail(trans->error), Object();

    return cont;
}

KAI_END

// EOF
