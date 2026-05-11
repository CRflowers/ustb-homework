#include "accountrecord.h"

//AccountRecord 记录账户类实现

AccountRecord::AccountRecord(Date pDate,const Account* pAccount,double pAmount,double pBalance,string pDesc):
    date(pDate),account(pAccount),amount(pAmount),balance(pBalance),desc(pDesc){

}

void AccountRecord::show(){
    /*
    date.show();cout <<  "\t#" << account->getId() << "\t" << amount <<
        "\t" << balance << "\t" << desc << endl;
    需要改
    */

}
