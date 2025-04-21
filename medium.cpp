import jakarta.persistence.*;

@Entity
public class Student {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String name;
    private int age;

    // getters and setters
}

import org.hibernate.*;
import org.hibernate.cfg.Configuration;

public class StudentDao {
    private static SessionFactory factory = new Configuration().configure().buildSessionFactory();

    public void saveStudent(Student s) {
        Session session = factory.openSession();
        Transaction tx = session.beginTransaction();
        session.save(s);
        tx.commit();
        session.close();
    }

    // Implement readStudent, updateStudent, deleteStudent similarly
}

public class TestCrud {
    public static void main(String[] args) {
        StudentDao dao = new StudentDao();

        Student s = new Student();
        s.setName("John");
        s.setAge(20);
        dao.saveStudent(s);
    }
}
