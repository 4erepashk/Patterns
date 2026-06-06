#include <iostream>
#include <thread>
#include <string>

// Фабрика //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Base
{
    public:
        virtual void doSome() = 0;
        virtual ~Base() = default;
};

class AProd : public Base
{
public:
    ~AProd(){};

    void doSome() override { printf( "AProd\n" ); }
};

class BProd : public Base
{
public:
    ~BProd(){};

    void doSome() override { printf( "BProd\n" ); }
};

class Creator 
{
    public:
        virtual Base * create() = 0;
        virtual ~Creator() = default;
        void doingSome() 
        {
            Base * prod = create();
            prod->doSome();

            if ( prod )
            {
                delete prod;
                prod = nullptr;
            }
        }
};

class CreatorA : public Creator
{
public:
    Base * create() override
    {
        return new AProd();
    }
};

class CreatorB : public Creator
{
public:
    Base * create() override
    {
        return new BProd();
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Singleton //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Worker
{
    public:
        Worker()
        : counter (0)
        {
    
        }

        ~Worker(){}

        static Worker * instance()
        {
            static Worker * w = new Worker();
            return w;
        }

        void someFunc()
        {
            printf( "%d\n", counter );
            counter++;
            printf( "%d\n", counter );
        }
    
    private:

    int counter;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Абстрактная фабрика //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class A { public: virtual void testPrint() = 0; virtual ~A() = default; };
class B { public: virtual void testPrint() = 0; virtual ~B() = default; };

class ACompl : public A { public: void testPrint() override { printf("A\n"); } };
class BCompl : public B { public: void testPrint() override { printf("B\n"); } };

class Factory
{
    public: 
    virtual A * createA() = 0;
    virtual B * createB() = 0;
};

class ABFacroty : public Factory
{
    public:
    A * createA() override { return new ACompl(); }
    B * createB() override { return new BCompl(); }
    void doWork() 
    {
        A * a = createA();
        B * b = createB();

        a->testPrint();
        b->testPrint();

        if ( a )
        {
            delete a;
            a = nullptr;
        }

        if ( b )
        {
            delete b;
            b = nullptr;
        }
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Строитель //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Packet
{
    public:

    std::string header;
    std::string part1;
    std::string part2;

    void doWork()
    {
        printf( "Header: %s\n", header.c_str() );
        printf( "Part1: %s\n", part1.c_str() );
        printf( "Part2: %s\n", part2.c_str() );
    }
};

class PacketBuilder
{
    Packet p;

    public:

    PacketBuilder & header( const std::string & str ) { p.header = str; return *this; }
    PacketBuilder & part1 ( const std::string & str ) { p.part1 = str; return *this; }
    PacketBuilder & part2 ( const std::string & str ) { p.part2 = str; return *this; }

    Packet build() { return p; }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Прототип //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Shape
{
    public:
        virtual Shape * copy() const = 0;
        virtual ~Shape() = default;
};

class SomeObject : public Shape
{
    public:

        int m_smth;
        SomeObject( int smth ) 
        : m_smth( smth ) {}
        Shape * copy() const override {  return new SomeObject( *this ); }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Адаптер //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    // Порождающие паттерны
    std::cout << "------------------------------------------------\n";
    std::cout << "Fabric\n";
    CreatorA ca;
    std::cout << "CreatorA create\n";
    ca.doingSome();
    CreatorB cb;
    std::cout << "CreatorB create\n";
    cb.doingSome();
    std::cout << "------------------------------------------------\n";

    std::cout << "------------------------------------------------\n";
    std::cout << "Singleton\n";
    Worker::instance()->someFunc();
    Worker::instance()->someFunc();
    std::cout << "------------------------------------------------\n";

    std::cout << "------------------------------------------------\n";
    std::cout << "Abstract factory\n";
    ABFacroty ab;
    ab.doWork();
    std::cout << "------------------------------------------------\n";

    std::cout << "------------------------------------------------\n";
    std::cout << "Builder\n";
    Packet pack = PacketBuilder().header( "header" )
                                 .part1 ( "part1" )
                                 .part2 ( "part2" )
                                 .build();
    pack.doWork();
    std::cout << "------------------------------------------------\n";

    std::cout << "------------------------------------------------\n";
    std::cout << "Prototype\n";

    SomeObject * orig = new SomeObject( 123 );
    SomeObject * copy = static_cast<SomeObject *>( orig->copy() );
    printf("Orig value %d\n", orig->m_smth );
    printf("Copy value %d\n", copy->m_smth );

    std::cout << "------------------------------------------------\n";

    // Структурные паттерны


    return 0;
}