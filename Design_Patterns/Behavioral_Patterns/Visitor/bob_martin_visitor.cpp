// Acyclic Visitor is a degenerate base class for all visitors.
class Visitor {
public:
    virtual ~Visitor() = 0;
    // The destructor is virtual, as all destructors ought to be.
    // it is also pure to prevent anyone from creating an
    // instance of Visitor. Since this class is going to be
    // used in a dynamic_cast expression, it must have at least
    // one virtual function.
};

class Modem {
public:
    virtual void Accept(Visitor&) const = 0;
};

class HayesModem;

class HayesModemVisitor {
public:
    virtual void Visit(HayesModem&) const = 0;
};

class HayesModem : public Modem {
public:
    virtual void Accept(Visitor& v) const;
};

void HayesModem::Accept(Visitor& v) const {
    if (HayesModemVisitor* hv = dynamic_cast<HayesModemVisitor*>(&v))
        hv->Visit(*this);
    else
    // AcceptError
}

class ZoomModem;

class ZoomModemVisitor {
public:
    virtual void Visit(ZoomModem&) const = 0;
};

class ZoomModem : public Modem {
public:
    virtual void Accept(Visitor& v) const;
};

void ZoomModem::Accept(Visitor& v) const {
    if (ZoomModemVisitor* zv = dynamic_cast<ZoomModemVisitor*>(&v))
        zv->Visit(*this);
    else
    // AcceptError
}

//-------------------------
// ConfigureForDOSVisitor
//
// This visitor configures both Hayes and Zoom modems
// for DOS.
//
class ConfigureForDosVisitor : public Visitor, public HayesModemVisitor, public ZoomModemVisitor {
public:
    virtual void Visit(HayesModem&); // configure Hayes for DOS
    virtual void Visit(ZoomModem&); // configure Zoom for DOS
};

//--------------------------
// ConfigureForUnixVisitor
//
// This visitor configures only Zoom modems for Unix
//
class ConfigureForUnixVisitor : public Visitor, public ZoomModemVisitor {
public:
    virtual void Visit(ZoomModem&); // configure Zoom for Unix
};
