#include <iostream>
#include <vector>
#include <string>

using namespace std; // namespace std ���

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
    vector<Book> books; // å ��� ���� 

public:
    // [1��] å �߰� �޼���
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back ���
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
    }

    // [2��] ��� å ��� �޼���
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (int i = 0; i < books.size(); i++) { // �Ϲ����� for�� ���
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    // [3��] å ���� �˻� �޼���
    void searchByTitle(const string& title) {

        bool found = false; // for�� �ٱ����� ����ó���� �ϱ� ���� �߰�!

        for (int i = 0; i < books.size(); ++i) {
            if (books[i].title == title) {
                cout << "�˻��� ����:" << endl;
                cout << "- " << books[i].title << " by " << books[i].author << endl;
                found = true;
                break; // break�� if�� ������� �ݺ����� ���������� ������ �̷��� ��� ����!
            }
        }

        if (!found) {
            cout << "�˻��� ������ ����� �����ϴ�. �ٽ� �õ��� �ּ���." << endl;
        }
    }

    // [4��] å ���� �˻� �޼���
    void searchByAuthor(const string& author) {
        for (int i = 0; i < books.size(); ++i) {
            if (books[i].author == author) {
                cout << "�˻��� ����:" << endl;
                cout << "- " << books[i].title << " by " << books[i].author << endl;
                break; // break�� if�� ������� �ݺ����� ���������� ������ �̷��� ��� ����!
            }
            else cout << "�˻��� ������ ����� �����ϴ�. �ٽ� �õ��� �ּ���." << endl;
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
        cout << "3. å �������� ���ϴ� å �˻� " << endl; // å �������� �˻� �߰�!
        cout << "4. å ���ڷ� ���ϴ� å �˻�" << endl; // ���� �������� �˻� �߰�!
        cout << "5. ����" << endl; // ���α׷� ����
        cout << "����: ";

        int choice; // ������� �޴� ������ ����
        cin >> choice;

        if (choice == 1) {
            // 1�� ����: å �߰�
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager.addBook(title, author); // �Է¹��� å ������ �߰�
        }
        else if (choice == 2) {
            // 2�� ����: ��� å ���
            // ���� BookManager�� ����� å ����� ����մϴ�.
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3�� ����: å �������� �˻� �߰�!
            while (true) {
                string title;
                cout << "(�˻��� ������������ '!' �Է�!)" << endl;
                cout << "å ����:";
                cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
                getline(cin, title); // ���� �Է� (���� ����)

                if (title == "!") {
                    cout << "���� �˻��� �����մϴ�!" << endl;
                    break;
                }
                manager.searchByTitle(title);
            }
        }
        else if (choice == 4) {
            // 4�� ����: ���� �������� �˻� �߰�!
            string author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, author); // ���� �Է� (���� ����)
            manager.searchByAuthor(author);
        }
        else if (choice == 5) {
            // 5�� ����: ����
            // ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
            cout << "���α׷��� �����մϴ�." << endl;
            break; // while ���� ����
        }
        else {
            // �߸��� �Է� ó��
            // �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0; // ���α׷� ���� ����
}
