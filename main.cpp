#include <iostream>
#include <memory>


// полёт
class FlyBehavior {
public:
    virtual void fly() const = 0;
    virtual ~FlyBehavior() = default;
};

class FlyWithWings : public FlyBehavior {
public:
    void fly() const override {
        std::cout << "*flies*\n";
    }
};

class FlyNoWay : public FlyBehavior {
public:
    void fly() const override {
        std::cout << "i can't fly ;(\n";
    }
};

// крякание
class QuackBehavior {
public:
    virtual void quack() const = 0;
    virtual ~QuackBehavior() = default;
};

class Quack : public QuackBehavior {
public:
    void quack() const override {
        std::cout << "QUACK!\n";
    }
};

class Squeak : public QuackBehavior {
public:
    void quack() const override {
        std::cout << "SQUEAK!\n";
    }
};

class MuteQuack : public QuackBehavior {
public:
    void quack() const override {
        std::cout << "*muted quack*\n";
    }
};

// класс утки
class Duck {
public:
    std::unique_ptr<FlyBehavior> flyBehavior; // unique_ptr - это умный указатель, который работает с некоторым
    std::unique_ptr<QuackBehavior> quackBehavior; // объектом этого класса, т.е. мы можем в конструкторе
    // присвоить наследника Behavior (в наследниках) и не переопределять методы performQuack() и performFly().
    // то есть это всё для того, чтобы не создавать объекты классов вручную, но при этом менять поведение
    // классов-наследников (например, у MallardDuck будет FlyWithWings и Quack вместо FlyBehavior и QuackBehavior)
    Duck(std::unique_ptr<FlyBehavior> flyBehavior, std::unique_ptr<QuackBehavior> quackBehavior)
    : flyBehavior(std::move(flyBehavior)), quackBehavior(std::move(quackBehavior)) {}
    void swim() {
        std::cout << "*water splashes* (all ducks swim)\n";
    }
    virtual void display() = 0;
    void performQuack() const {
        quackBehavior->quack();
    }
    void performFly() const {
        flyBehavior->fly();
    }
    void setFlyBehavior(std::unique_ptr<FlyBehavior> fb) {
        this->flyBehavior = std::move(fb);
    }
    void setQuackBehavior(std::unique_ptr<QuackBehavior> qb) {
        this->quackBehavior = std::move(qb);
    }
};

// make_unique - возвращает unique_ptr передаваемого класса/типа данных

// утки
class MallardDuck : public Duck {
public:
    MallardDuck() : Duck(std::make_unique<FlyWithWings>(), std::make_unique<Quack>()) {}

    void display() override {
        std::cout << "MallardDuck!\n";
    }
};

class RedheadDuck : public Duck {
public:
    RedheadDuck() : Duck(std::make_unique<FlyWithWings>(), std::make_unique<Quack>()) {}

    void display() override {
        std::cout << "RedheadDuck!\n";
    }
};

class RubberDuck : public Duck {
public:
    RubberDuck() : Duck(std::make_unique<FlyNoWay>(), std::make_unique<Squeak>()) {}

    void display() override {
        std::cout << "*...just a RubberDuck, I guess...*\n";
    }
};

class DecoyDuck : public Duck {
public:
    DecoyDuck() : Duck(std::make_unique<FlyNoWay>(), std::make_unique<MuteQuack>()) {}

    void display() override {
        std::cout << "no comments, DecoyDuck (not a real one)\n";
    }
};


int main() {
    MallardDuck mallardDuck;
    mallardDuck.display();
    mallardDuck.performFly();
    mallardDuck.swim();

    RedheadDuck redheadDuck;
    redheadDuck.display();
    redheadDuck.performFly();
    redheadDuck.swim();

    RubberDuck rubberDuck;
    rubberDuck.display();
    rubberDuck.performFly();
    rubberDuck.swim();

    DecoyDuck decoyDuck;
    decoyDuck.display();
    decoyDuck.performFly();
    decoyDuck.swim();


    return 0;
}
