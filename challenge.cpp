#include <iostream>
#include <vector>
#include <string>
#include <unordered_map> // unordered_map 추가!!

using namespace std;


class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {}
};

class BorrowManager {
private:
    // 왜 unordered_map을 썼을까? 조회를 빨리 하기 위해서!
    unordered_map<string, int> stocks; // stock은 도서의 재고 정보를 관리함.
public:
    // 맵 구조에서는 stock[key]가 뒤에 value값이라고 생각하면 된다.
    void addStock(const string& title, int quantity = 3) {
        stocks[title] = quantity;
    }

    // 대출 가능 여부 확인 및 재고 업데이트
    bool borrowBook(const string& title) {
        if (stocks[title] > 0) {
            stocks[title]--;
            return true; // 대출 가능
        }
        else {
            return false; // 대출 불가
        }
    }

    // 반납 처리
    bool returnBook(const string& title) {
        auto it = stocks.find(title);
        if (it != stocks.end() && stocks[title] < 3) {
            stocks[title]++;
            return true; // 반납 성공
        }
        return false; // 반납 불가 (최대 재고 초과)
    }

    void displayStock() const {
        if (stocks.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }
        cout << "<현재 도서 목록>" << endl;

        // 여기서 auto는 stock의 타입이다. pair<string, int>가 될 것이다.
        for (auto& stock : stocks) {
            cout << "책 제목 : " << stock.first << " | 현재 재고 수 : " << stock.second << endl;
        }
    }

    // 현재 재고 수
    int getStock(const string& title) const {
        auto it = stocks.find(title);
        if (it != stocks.end()) {
            return it->second;
        }
        return -1; // 책이 없으면 -1 반환
    }

    // 대출 여부
    bool canBorrowStock(const Book* book) const {
        auto it = stocks.find(book->title);
        if (it != stocks.end()) {
            return it->second == 3;
        }
        return false; // 책이 없으면 대출 불가
    }
};

class BookManager {
private:
    vector<Book*> books; // 책 목록 저장 
    BorrowManager borrowManager; // BorrowManager와 연동

public:
    // 소멸자
    ~BookManager() {
        for (Book* book : books) {
            delete book;
        }
    }

    // [1번] 책 추가 
    void addBook(const string& title, const string& author) {
        books.push_back(new Book(title, author)); // push_back 사용
        borrowManager.addStock(title);
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // [2번] 모든 책 출력 
    void displayStocks() const {
        borrowManager.displayStock();
    }

    // 책 제목으로 책 찾아서 메모리 주소 반환
    Book* findByTitle(const string& title) {
        for (Book* book : books) {
            if (book->title == title) {
                return book; // Book* 타입 반환
            }
        }
        return nullptr; // 없으면 nullptr 반환
    }

    // 책 저자로 책 찾아서 메모리 주소 반환
    Book* findByAuthor(const string& author) {
        for (Book* book : books) {
            if (book->author == author) {
                return book; // Book* 타입 반환
            }
        }
        return nullptr; // 없으면 nullptr 반환
    }

    // 책 제목으로 대여
    void borrowByTitle(const string& title) {
        Book* book = findByTitle(title);
        if (!book) {
            cout << "대출하려는 도서가 존재하지 않습니다: " << title << endl;
            return;
        }

        if (borrowManager.borrowBook(title)) {
            cout << book->title << " by " << book->author << " 를 대출했습니다." << endl;
            cout << "남은 재고: " << borrowManager.getStock(title) << endl;
        }
        else {
            cout << book->title << " by " << book->author << " 의 재고가 없습니다. 죄송합니다." << endl;
        }
    }

    // 책 저자로 대여
    void borrowByAuthor(const string& author) {
        Book* book = findByAuthor(author);
        if (!book) {
            cout << "대출하려는 도서가 존재하지 않습니다: " << author << endl;
            return;
        }

        if (borrowManager.borrowBook(book->title)) {
            cout << book->title << " by " << book->author << " 를 대출했습니다." << endl;
            cout << "남은 재고: " << borrowManager.getStock(book->title) << endl;
        }
        else {
            cout << book->title << " by " << book->author << " 의 재고가 없습니다. 죄송합니다." << endl;
        }
    }

    // 책 반납
    void returnBook(const string& title) {
        Book* book = findByTitle(title);
        if (!book) {
            cout << "반납하려는 도서가 존재하지 않습니다: " << title << endl;
            return;
        }

        if (borrowManager.returnBook(title)) {
            cout << book->title << " by " << book->author << " 를 반납하셨습니다." << endl;
            cout << "현재 재고: " << borrowManager.getStock(title) << endl;
        }
        else {
            cout << book->title << " by " << book->author
                << " 를 모두 반납하셨습니다. 더 이상 반납할 수 없습니다." << endl;
        }
    }

    // 만약에 데이터가 늘어나면 BorrowManager에 status를 추가하고 초기화하면
    // 그만큼 메모리를 더 잡아먹으니까 일부러 if문 안에 넣어서 쓰이고 나면 사라지게 했다.
    void searchByTitle(const string& title) {
        bool canISearch = false;
        for (Book* book : books) {
            if (book->title == title) {
                string status = "";
                canISearch = true;
                // BorrowManager에서 대여 상태 조회
                if (borrowManager.canBorrowStock(book)) {
                    status = "미대여";
                }
                else {
                    status = "대여중";
                }

                cout << "<제목 검색>" << endl;
                cout << "- " << book->title << " by " << book->author
                    << " | 대여 여부 : " << status << endl;
            }
        }  
        if(!canISearch){
            cout << "검색한 제목의 도서가 없습니다. 다시 시도해 주세요." << endl;
        }
    }

    void searchByAuthor(const string& author) {
        bool canISearch2 = false;
        for (Book* book : books) {
            if (book->author == author) {
                string status = "";
                canISearch2 = true;
                // BorrowManager에서 대여 상태 조회
                if (borrowManager.canBorrowStock(book)) {
                    status = "미대여";
                }
                else {
                    status = "대여중";
                }

                cout << "<저자 검색>" << endl;
                cout << "- " << book->title << " by " << book->author
                    << " | 대여 여부 : " << status << endl;
            }
        }
        if (!canISearch2) {
            cout << "검색한 제목의 도서가 없습니다. 다시 시도해 주세요." << endl;
        }
    }
};

int main() {
    BookManager manager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책 제목으로 검색 " << endl; // 책 제목으로 검색 추가!
        cout << "4. 책 저자로 검색" << endl; // 책의 저자로 검색 추가!
        cout << "5. 책 제목으로 대여" << endl; // 책 제목으로 대여
        cout << "6. 책 저자로 대여" << endl; // 첵의 저자로 대여
        cout << "7. 빌린 책 반납하기" << endl; // 빌린 책 반납하기(제목)
        cout << "8. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가 | 여기서 Book 객체 생성
        }
        else if (choice == 2) {
            manager.displayStocks();
        }
        // 책 검색
        else if (choice == 3) {
            string title;
            cout << "책 제목:";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            manager.searchByTitle(title);
        }
        else if (choice == 4) {
            string author;
            cout << "책 저자: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, author); // 저자 입력 (공백 포함)
            manager.searchByAuthor(author);
        }
        // 책 대여
        else if (choice == 5) {
            string title;
            cout << "책 제목:";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            manager.borrowByTitle(title);
        }
        else if (choice == 6) {
            string author;
            cout << "책 저자: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, author); // 저자 입력 (공백 포함)
            manager.borrowByAuthor(author);
        }
        // 책 반납
        else if (choice == 7) {
            string title;
            cout << "책 제목:";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            manager.returnBook(title);
        }
        // 종료
        else if (choice == 8) {
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
            break;
        }
    }
    return 0; 
}
