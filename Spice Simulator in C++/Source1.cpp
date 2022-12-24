#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class mosfet {
public:
    string drain;
    string gate;
    string source;
    string body;
    string type;

    mosfet();
    mosfet(string d, string g, string s, string b,  string t);
    void output(vector<mosfet> pullup, vector <mosfet> pulldown, int count, vector<char> op);
    vector<mosfet> pullup(vector<char> op, vector<string> var, int w, char out);
    vector<mosfet> pulldown(vector<char> op, vector<string> var, int w, char out);
    void outputnegations(vector<string>var, int& mos);
};

mosfet::mosfet()
{
}

mosfet::mosfet(string d, string g, string s, string b, string t) {
    gate = g;
    drain = d;
    source = s;
    body = b;
    type = t;
}
void mosfet::output(vector<mosfet> pullup, vector <mosfet> pulldown, int count,vector<char> op)
{
    for (int i = 0; i < pullup.size(); i++)
    {
        cout << "M" << i + 1 + count << " " << pullup[i].drain << " " << pullup[i].gate << " " << pullup[i].source << " " << pullup[i].source << " " << pullup[i].type << endl;
    }
    for (int j = 0; j < pulldown.size(); j++)
    {
        cout << "M" << pulldown.size() + j + 1 + count << " " << pulldown[j].drain << " " << pulldown[j].gate << " " << pulldown[j].source << " " << pulldown[j].source << " " << pulldown[j].type << endl;
    }
}
vector<mosfet>mosfet::pullup(vector<char> op, vector<string> var, int wire, char out) {
    vector<mosfet>outpull_up;
    int check1 = 0, check2 = 0;

    int i = 0;

    while (i < op.size())
    {

        if (op[i] == '&') {
            check2++;

        }

        else {

            int j = check1;
            while (j <= check2) {
                gate = var[j];
                type = "PMOS";
                if (j == check1) {
                    source = "Vdd";
                    body = "Vdd";
                }
                else {
                    source = to_string(wire);
                    body = to_string(wire);
                }

                if (i == check2) {
                    wire++;
                    drain = out;

                }
                else {
                    wire++;
                    drain = to_string(wire);

                }

                outpull_up.push_back(*this);

                j++;
            }
            wire++;
            check2++;
            check1 = check2;

        }

        i++;
    }


    int k = check1;
    while (k <= check2) {
        gate = var[k];
        type = "PMOS";
        if (k == check1) {
            source = "Vdd";
            body = "Vdd";
        }
        else {
            source = to_string(wire);
            body = to_string(wire);
        }
        if (k == check2) {

            drain = out;

        }
        else {

            drain = out;
        }

        outpull_up.push_back(*this);

        k++;
    }

    return outpull_up;
}
vector<mosfet>mosfet::pulldown(vector<char> op, vector<string> var, int wire, char out) {
    vector<mosfet>outpulldown;
    int check1 = 0;
    int check2 = 0;
    int wireS = 0;
    int wireD = wire + 1;
    for (int i = 0; i < var.size(); i++)
    {
        if (var[i].size() > 1)
        {
            var[i] = var[i][0];
        }
        else {
            var[i] = var[i] + '\'';
        }
    }
    int i = 0;

    while (i < op.size()) {
        if (op[i] == '&') {
            check2++;
        }
        else {
            int j = check1;
            while (j <= check2) {
                type = "NMOS";
                gate = var[j];
                drain = to_string(wireD);
                source = to_string(wireS);
                body =  to_string(wireS);

                outpulldown.push_back(*this);

                j++;
            }

            wire++;
            wireS = wireD;
            wireD++;
            check2++;
            check1 = check2;
        }

        i++;
    }

    drain = out;

    int k = check1;
    while (k <= check2) {
        type = "NMOS";
        gate = var[k];
        source =  to_string(wireS);
        body =  to_string(wireS);

        outpulldown.push_back(*this);

        k++;
    }

    return outpulldown;
}

void mosfet::outputnegations(vector<string>var, int& mos){
for (int i = 0; i < var.size(); i++)
{
    if (var[i].size() == 1)
    {
        mos++;
        cout << "M" << mos << " " << var[i] << " " << var[i] + '\'' << " VDD VDD PMOS" << endl;
        mos++;
        cout << "M" << mos << " " << var[i] << " " << var[i] + '\'' << " 0 0 NMOS" << endl;
    }
    else {
        mos++;
        cout << "M" << mos << " " << var[i] << " " << var[i][0] << " VDD VDD PMOS" << endl;
        mos++;
        cout << "M" << mos << " " << var[i] << " " << var[i][0] << " 0 0 NMOS" << endl;
    }

}
}

int main()
{
    string expression;
    vector<string>var;
    vector<char>op;
    mosfet exp;
    vector<mosfet> pullup;
    vector<mosfet> pulldown;
    int v = 0;
    int o = 0;
    int w = 0;
    int mos = 0;
   
    cout << "Enter the boolean expression:";
    cin >> expression;
    char y = expression[0];
    for (int i = 2; i < expression.size(); i++)
    {
        //cout << expression[i] << endl;
        if (expression[i] == expression[0])
        {
            cout << "Invalid boolean expression";
            return 0;

        }
        else {
            if (expression[i] == '&' || expression[i] == '|')
            {
                o++;
                op.resize(o);
                op[o - 1] = expression[i];


            }
         
                else
                {
                    if (i == expression.size() - 1 && expression[i] != '\'')
                    {
                        v++;
                        var.resize(v);
                        var[v - 1] = expression[i];
                        
                    }
                    else 
                    {
                        if (expression[i + 1] == '\'')
                        {
                            
                        }
                        else
                        {
                            if (expression[i] == '\'')
                            {
                                v++;
                                var.resize(v);
                                var[v - 1] = expression[i-1];
                                var[v - 1].push_back('\'');
                            }
                            else {
                                v++;
                                var.resize(v);
                                var[v - 1] = expression[i];
                                

                            }
                         

                        }


                    }

                }
            
            
        }
    }
   /* for (int i = 0; i < op.size(); i++)
    {
        cout << endl;
        cout << op[i] << endl;
    }
    for (int i = 0; i < var.size(); i++)
    {
        cout << endl;
        cout << var[i] << endl;
    }*/
   
    pullup = exp.pullup(op,var,  w, y);
    pulldown = exp.pulldown(op, var,  w, y);
    exp.outputnegations(var, mos);
    exp.output(pullup, pulldown, mos,op);

    return 0;
}

