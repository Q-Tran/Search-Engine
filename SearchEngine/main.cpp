/* Jakob Wells | Van Tran | SEARCH ENGINE PROJECT | main.cpp | Dec. 7th, 2015
 * Please see documentation for more details on the functioning of this program
 *
 */
#include "userinterface.h"

#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    //For the pure fun of it.
  cout << " (                 (              )           )          (        )       " << endl
       << " )\\ )       (      )\\ )   (    ( /(        ( /(  (       )\\ )  ( /(       " << endl
       << "(()/( (     )\\    (()/(   )\\   )\\())  (    )\\()) )\\ )   (()/(  )\\()) (    " << endl
       << " /(_)))\\ ((((_)(   /(_))(((_) ((_)\\   )\\  ((_)\\ (()/(    /(_))((_)\\  )\\   " << endl
       << "(_)) ((_) )\\ _ )\\ (_))  )\\___  _((_) ((_)  _((_) /(_))_ (_))   _((_)((_)  " << endl
       << "/ __|| __|(_)_\\(_)| _ \\((/ __|| || | | __|| \\| |(_)) __||_ _| | \\| || __| " << endl
       << "\\__ \\| _|  / _ \\  |   / | (__ | __ | | _| | .` |  | (_ | | |  | .` || _|  " << endl
       << "|___/|___|/_/ \\_\\ |_|_\\  \\___||_||_| |___||_|\\_|   \\___||___| |_|\\_||___| " << endl;

    UserInterface ui;

    //Lets get it started shall we?
    ui.startInterface();

    return 0;
}
