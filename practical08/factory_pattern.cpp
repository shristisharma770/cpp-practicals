// Practical 08: Factory Design Pattern
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class Notification {
public:
    virtual ~Notification() = default;
    virtual void send(const std::string& message) const = 0;
};

class EmailNotification : public Notification {
public:
    void send(const std::string& message) const override {
        std::cout << "Email sent: " << message << '\n';
    }
};

class SmsNotification : public Notification {
public:
    void send(const std::string& message) const override {
        std::cout << "SMS sent: " << message << '\n';
    }
};

class NotificationFactory {
public:
    static std::unique_ptr<Notification> create(const std::string& type) {
        if (type == "email")
            return std::unique_ptr<Notification>(new EmailNotification());
        if (type == "sms")
            return std::unique_ptr<Notification>(new SmsNotification());
        throw std::invalid_argument("Unsupported notification type: " + type);
    }
};

int main() {
    std::unique_ptr<Notification> email =
        NotificationFactory::create("email");
    std::unique_ptr<Notification> sms =
        NotificationFactory::create("sms");

    email->send("Your order has shipped.");
    sms->send("Your verification code is 4821.");

    std::cout << "\nBenefit: object creation is centralised and easy to extend.\n";
    std::cout << "Trade-off: the factory adds extra classes and branching.\n";
    return 0;
}
