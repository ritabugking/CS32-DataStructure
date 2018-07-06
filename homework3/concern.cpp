//
//  concern.cpp
//  homework3
//
//  Created by YI-JU WANG on 2018/5/9.
//  Copyright © 2018年 YI-JU WANG. All rights reserved.
//


class Concern{
public:
    Concern(string name);
    string person() const;
    virtual string description() const = 0;
    virtual bool possibleFelony() const;
    virtual ~Concern();
private:
    string m_name;
};

Concern::Concern(string name):m_name(name){}

string Concern::person() const
{
    return m_name;
};
    
bool Concern::possibleFelony() const
{
    return false;
};
Concern::~Concern(){}


class EthicsMatter: public Concern{
public:
    EthicsMatter(string name);
    virtual ~EthicsMatter();
    virtual string description() const;
private:
};

EthicsMatter::EthicsMatter(string name): Concern(name){}
string EthicsMatter::description() const{
    return "An ethics matter";
};
EthicsMatter::~EthicsMatter(){
    cout << "Destroying " << person() << "'s ethics matter" << endl;
}

class HushPayment: public Concern{
public:
    HushPayment(string name, int money);
    virtual ~HushPayment();
    virtual string description() const;
private:
    int m_money;
};

HushPayment::HushPayment(string name, int money): Concern(name), m_money(money){}
HushPayment::~HushPayment(){
    cout << "Destroying " << person() << "'s hush payment" << endl;
}
string HushPayment::description() const{
    return "A $"+to_string(m_money)+" payment";
};

class Investigation: public Concern{
public:
    Investigation(string name);
    virtual ~Investigation();
    virtual string description() const;
    virtual bool possibleFelony() const;
private:
};

Investigation::Investigation(string name): Concern(name){}
Investigation::~Investigation(){
    cout << "Destroying " << person() << "'s investigation" << endl;
}
string Investigation::description() const{
    return "An investigation";
};
bool Investigation::possibleFelony() const {return true;};



