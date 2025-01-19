#include <iostream>
#include <vector>
#include <string>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장 

public:
    // [1번] 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // [2번] 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (int i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    // [3번] 책 제목 검색 메서드
    void searchByTitle(const string& title) {

        bool found = false; // for문 바깥으로 예외처리를 하기 위해 추가!

        for (int i = 0; i < books.size(); ++i) {
            if (books[i].title == title) {
                cout << "검색한 도서:" << endl;
                cout << "- " << books[i].title << " by " << books[i].author << endl;
                found = true;
                break; // break는 if문 상관없이 반복문을 빠져나오기 때문에 이렇게 사용 가능!
            }
        }

        if (!found) {
            cout << "검색한 제목의 결과가 없습니다. 다시 시도해 주세요." << endl;
        }
    }

    // [4번] 책 저자 검색 메서드
    void searchByAuthor(const string& author) {
        for (int i = 0; i < books.size(); ++i) {
            if (books[i].author == author) {
                cout << "검색한 도서:" << endl;
                cout << "- " << books[i].title << " by " << books[i].author << endl;
                break; // break는 if문 상관없이 반복문을 빠져나오기 때문에 이렇게 사용 가능!
            }
            else cout << "검색한 제목의 결과가 없습니다. 다시 시도해 주세요." << endl;
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
        cout << "3. 책 제목으로 원하는 책 검색 " << endl; // 책 제목으로 검색 추가!
        cout << "4. 책 저자로 원하는 책 검색" << endl; // 저자 제목으로 검색 추가!
        cout << "5. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3번 선택: 책 제목으로 검색 추가!
            while (true) {
                string title;
                cout << "(검색을 빠져나오려면 '!' 입력!)" << endl;
                cout << "책 제목:";
                cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
                getline(cin, title); // 제목 입력 (공백 포함)

                if (title == "!") {
                    cout << "제목 검색을 종료합니다!" << endl;
                    break;
                }
                manager.searchByTitle(title);
            }
        }
        else if (choice == 4) {
            // 4번 선택: 저자 제목으로 검색 추가!
            string author;
            cout << "책 저자: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, author); // 저자 입력 (공백 포함)
            manager.searchByAuthor(author);
        }
        else if (choice == 5) {
            // 5번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}
