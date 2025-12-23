#include <vector>
#include <iostream>
/* Задание 3.
 * Не хватает переменной, в которой хранится АКТУАЛЬНОЕ количество объектов.
 * Для этого нужно знать теорию по копированию и move semantics.
 */
class Destination {
public:
    enum class City {
        KRASNODAR,
        ANAPA,
        SOCHI,
        NOVOSIBIRSK,
    };

    constexpr Destination(const City &city): city(city) { }

    std::string to_string() const {
        switch (this->city) {
            case City::KRASNODAR: return "Krasnodar";
            case City::ANAPA: return "Anapa";
            case City::SOCHI: return "Sochi";
            case City::NOVOSIBIRSK: return "Novosibirsk";
        }
        return "Unknown";
    }
private:
    City city;
};

class Person {
public:
    std::string first_name;
    std::string patronymic;
    std::string last_name;
    Person(const std::string &first_name, const std::string &patronymic, const std::string &last_name):
        first_name(first_name), patronymic(patronymic), last_name(last_name) { } 
};


class Month {
public:
    enum class Title {
        January,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };
    constexpr Month(const Title &title): title(title) { }
    std::string to_string() const {
        switch (this->title) {
            case Title::January: return "January";
            case Title::February: return "February";
            case Title::March: return "March";
            case Title::April: return "April";
            case Title::May: return "May";
            case Title::June: return "June";
            case Title::July: return "July";
            case Title::August: return "August";
            case Title::September: return "September";
            case Title::October: return "October";
            case Title::November: return "November";
            case Title::December: return "December";
        }
        return "Unknown";
    }
private:
    Title title;
};

class Date {
    int year;
    Month month;
    int day;

public:
    Date(const int &year, const Month &month, const int &day): year(year), month(month), day(day) { }
    friend std::ostream& operator<<(std::ostream &out, const Date &date) {
        out << date.month.to_string() << " " << date.day << ", " << date.year;
        return out;
    }
};

class Ticket {
    static int ticket_total_issued;
    const int ticket_number;
    Person person;
    Destination destination;
    Date desired_date;
public:
    Ticket(const Person &pers, const Destination &dest, const Date &date): person(pers), destination(dest), desired_date(date), ticket_number(++ticket_total_issued) { }
    static int get_total_count() { return ticket_total_issued; }
    friend std::ostream& operator<<(std::ostream &out, const Ticket &ticket) {
        out << ticket.ticket_number << ". Destination: " << ticket.destination.to_string() << "\nName: " << ticket.person.first_name << " " << ticket.person.patronymic << " "
        << ticket.person.last_name << "\nDate: " << ticket.desired_date;
        return out;
    }
};
int Ticket::ticket_total_issued = 0;

class TicketBase {
    std::vector<Ticket> tickets;
public:
    void print() {
        for (const Ticket &ticket: tickets) {
            std::cout << ticket << "\n";
        }
        std::cout << std::flush;
    }
    void add(const Ticket &ticket) {
        tickets.push_back(ticket);
    }

    void pop() {
        if (!tickets.empty()) {
            tickets.pop_back();
        }
    }

    int size() const {
        return tickets.size();
    }
};


int main(int argc, char *argv[]) {
    TicketBase database;
    Person misha("Mikhail", "Ivanovuch", "Verblud");
    Destination anapa(Destination::City::ANAPA);
    Date date(2013, Month::Title::July, 21);
    Ticket ticket(misha, anapa, date);
    database.add(ticket);

    Person alex("Alexey", "Petrovich", "Sobaka");
    Destination sochi(Destination::City::SOCHI);
    Date date2(2009, Month::Title::March, 15);
    Ticket ticket2(alex, sochi, date2);
    database.add(ticket2);

    Person anna("Anna", "Sergeevna", "Chmara");
    Destination novosib(Destination::City::NOVOSIBIRSK);
    Date date3(2016, Month::Title::December, 5);
    Ticket ticket3(anna, novosib, date3);
    database.add(ticket3);

    database.print();
    database.pop();
    std::cout << "\n\n\n";
    database.print();
}


