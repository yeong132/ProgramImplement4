#include <iostream>
#include <vector>
#include <string>
#include <unordered_map> // unordered_map �߰�!!

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
    // �� unordered_map�� ������? ��ȸ�� ���� �ϱ� ���ؼ�!
    unordered_map<string, int> stocks; // stock�� ������ ��� ������ ������.
public:
    // �� ���������� stock[key]�� �ڿ� value���̶�� �����ϸ� �ȴ�.
    void addStock(const string& title, int quantity = 3) {
        stocks[title] = quantity;
    }

    // ���� ���� ���� Ȯ�� �� ��� ������Ʈ
    bool borrowBook(const string& title) {
        if (stocks[title] > 0) {
            stocks[title]--;
            return true; // ���� ����
        }
        else {
            return false; // ���� �Ұ�
        }
    }

    // �ݳ� ó��
    bool returnBook(const string& title) {
        auto it = stocks.find(title);
        if (it != stocks.end() && stocks[title] < 3) {
            stocks[title]++;
            return true; // �ݳ� ����
        }
        return false; // �ݳ� �Ұ� (�ִ� ��� �ʰ�)
    }

    void displayStock() const {
        if (stocks.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }
        cout << "<���� ���� ���>" << endl;

        // ���⼭ auto�� stock�� Ÿ���̴�. pair<string, int>�� �� ���̴�.
        for (auto& stock : stocks) {
            cout << "å ���� : " << stock.first << " | ���� ��� �� : " << stock.second << endl;
        }
    }

    // ���� ��� ��
    int getStock(const string& title) const {
        auto it = stocks.find(title);
        if (it != stocks.end()) {
            return it->second;
        }
        return -1; // å�� ������ -1 ��ȯ
    }

    // ���� ����
    bool canBorrowStock(const Book* book) const {
        auto it = stocks.find(book->title);
        if (it != stocks.end()) {
            return it->second == 3;
        }
        return false; // å�� ������ ���� �Ұ�
    }
};

class BookManager {
private:
    vector<Book*> books; // å ��� ���� 
    BorrowManager borrowManager; // BorrowManager�� ����

public:
    // �Ҹ���
    ~BookManager() {
        for (Book* book : books) {
            delete book;
        }
    }

    // [1��] å �߰� 
    void addBook(const string& title, const string& author) {
        books.push_back(new Book(title, author)); // push_back ���
        borrowManager.addStock(title);
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
    }

    // [2��] ��� å ��� 
    void displayStocks() const {
        borrowManager.displayStock();
    }

    // å �������� å ã�Ƽ� �޸� �ּ� ��ȯ
    Book* findByTitle(const string& title) {
        for (Book* book : books) {
            if (book->title == title) {
                return book; // Book* Ÿ�� ��ȯ
            }
        }
        return nullptr; // ������ nullptr ��ȯ
    }

    // å ���ڷ� å ã�Ƽ� �޸� �ּ� ��ȯ
    Book* findByAuthor(const string& author) {
        for (Book* book : books) {
            if (book->author == author) {
                return book; // Book* Ÿ�� ��ȯ
            }
        }
        return nullptr; // ������ nullptr ��ȯ
    }

    // å �������� �뿩
    void borrowByTitle(const string& title) {
        Book* book = findByTitle(title);
        if (!book) {
            cout << "�����Ϸ��� ������ �������� �ʽ��ϴ�: " << title << endl;
            return;
        }

        if (borrowManager.borrowBook(title)) {
            cout << book->title << " by " << book->author << " �� �����߽��ϴ�." << endl;
            cout << "���� ���: " << borrowManager.getStock(title) << endl;
        }
        else {
            cout << book->title << " by " << book->author << " �� ��� �����ϴ�. �˼��մϴ�." << endl;
        }
    }

    // å ���ڷ� �뿩
    void borrowByAuthor(const string& author) {
        Book* book = findByAuthor(author);
        if (!book) {
            cout << "�����Ϸ��� ������ �������� �ʽ��ϴ�: " << author << endl;
            return;
        }

        if (borrowManager.borrowBook(book->title)) {
            cout << book->title << " by " << book->author << " �� �����߽��ϴ�." << endl;
            cout << "���� ���: " << borrowManager.getStock(book->title) << endl;
        }
        else {
            cout << book->title << " by " << book->author << " �� ��� �����ϴ�. �˼��մϴ�." << endl;
        }
    }

    // å �ݳ�
    void returnBook(const string& title) {
        Book* book = findByTitle(title);
        if (!book) {
            cout << "�ݳ��Ϸ��� ������ �������� �ʽ��ϴ�: " << title << endl;
            return;
        }

        if (borrowManager.returnBook(title)) {
            cout << book->title << " by " << book->author << " �� �ݳ��ϼ̽��ϴ�." << endl;
            cout << "���� ���: " << borrowManager.getStock(title) << endl;
        }
        else {
            cout << book->title << " by " << book->author
                << " �� ��� �ݳ��ϼ̽��ϴ�. �� �̻� �ݳ��� �� �����ϴ�." << endl;
        }
    }

    // ���࿡ �����Ͱ� �þ�� BorrowManager�� status�� �߰��ϰ� �ʱ�ȭ�ϸ�
    // �׸�ŭ �޸𸮸� �� ��Ƹ����ϱ� �Ϻη� if�� �ȿ� �־ ���̰� ���� ������� �ߴ�.
    void searchByTitle(const string& title) {
        bool canISearch = false;
        for (Book* book : books) {
            if (book->title == title) {
                string status = "";
                canISearch = true;
                // BorrowManager���� �뿩 ���� ��ȸ
                if (borrowManager.canBorrowStock(book)) {
                    status = "�̴뿩";
                }
                else {
                    status = "�뿩��";
                }

                cout << "<���� �˻�>" << endl;
                cout << "- " << book->title << " by " << book->author
                    << " | �뿩 ���� : " << status << endl;
            }
        }  
        if(!canISearch){
            cout << "�˻��� ������ ������ �����ϴ�. �ٽ� �õ��� �ּ���." << endl;
        }
    }

    void searchByAuthor(const string& author) {
        bool canISearch2 = false;
        for (Book* book : books) {
            if (book->author == author) {
                string status = "";
                canISearch2 = true;
                // BorrowManager���� �뿩 ���� ��ȸ
                if (borrowManager.canBorrowStock(book)) {
                    status = "�̴뿩";
                }
                else {
                    status = "�뿩��";
                }

                cout << "<���� �˻�>" << endl;
                cout << "- " << book->title << " by " << book->author
                    << " | �뿩 ���� : " << status << endl;
            }
        }
        if (!canISearch2) {
            cout << "�˻��� ������ ������ �����ϴ�. �ٽ� �õ��� �ּ���." << endl;
        }
    }
};

int main() {
    BookManager manager;

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. å �������� �˻� " << endl; // å �������� �˻� �߰�!
        cout << "4. å ���ڷ� �˻�" << endl; // å�� ���ڷ� �˻� �߰�!
        cout << "5. å �������� �뿩" << endl; // å �������� �뿩
        cout << "6. å ���ڷ� �뿩" << endl; // ý�� ���ڷ� �뿩
        cout << "7. ���� å �ݳ��ϱ�" << endl; // ���� å �ݳ��ϱ�(����)
        cout << "8. ����" << endl; // ���α׷� ����
        cout << "����: ";

        int choice; // ������� �޴� ������ ����
        cin >> choice;

        if (choice == 1) {
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager.addBook(title, author); // �Է¹��� å ������ �߰� | ���⼭ Book ��ü ����
        }
        else if (choice == 2) {
            manager.displayStocks();
        }
        // å �˻�
        else if (choice == 3) {
            string title;
            cout << "å ����:";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            manager.searchByTitle(title);
        }
        else if (choice == 4) {
            string author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, author); // ���� �Է� (���� ����)
            manager.searchByAuthor(author);
        }
        // å �뿩
        else if (choice == 5) {
            string title;
            cout << "å ����:";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            manager.borrowByTitle(title);
        }
        else if (choice == 6) {
            string author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, author); // ���� �Է� (���� ����)
            manager.borrowByAuthor(author);
        }
        // å �ݳ�
        else if (choice == 7) {
            string title;
            cout << "å ����:";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            manager.returnBook(title);
        }
        // ����
        else if (choice == 8) {
            cout << "���α׷��� �����մϴ�." << endl;
            break; // while ���� ����
        }
        else {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
            break;
        }
    }
    return 0; 
}
