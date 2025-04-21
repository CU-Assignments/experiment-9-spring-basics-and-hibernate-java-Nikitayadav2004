@Entity
public class Account {
    @Id
    private int accountId;
    private String holderName;
    private double balance;

    // getters and setters
}
@Entity
public class Transaction {
    @Id
    @GeneratedValue
    private int transactionId;
    private int fromAccount;
    private int toAccount;
    private double amount;
    private Date date = new Date();

    // getters and setters
}
@Configuration
@EnableTransactionManagement
@ComponentScan("com.example")
public class AppConfig {

    @Bean
    public DataSource dataSource() { ... }

    @Bean
    public LocalSessionFactoryBean sessionFactory() { ... }

    @Bean
    public HibernateTransactionManager transactionManager(SessionFactory sessionFactory) {
        return new HibernateTransactionManager(sessionFactory);
    }
}

@Service
public class BankService {
    @Autowired
    private SessionFactory factory;

    @Transactional
    public void transferMoney(int fromId, int toId, double amount) {
        Session session = factory.getCurrentSession();

        Account from = session.get(Account.class, fromId);
        Account to = session.get(Account.class, toId);

        if (from.getBalance() < amount) {
            throw new RuntimeException("Insufficient funds");
        }

        from.setBalance(from.getBalance() - amount);
        to.setBalance(to.getBalance() + amount);

        Transaction txn = new Transaction();
        txn.setFromAccount(fromId);
        txn.setToAccount(toId);
        txn.setAmount(amount);
        session.save(txn);
    }
}

public class MainApp {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(AppConfig.class);
        BankService service = context.getBean(BankService.class);

        try {
            service.transferMoney(101, 102, 500);
            System.out.println("Transaction successful");
        } catch (Exception e) {
            System.out.println("Transaction failed: " + e.getMessage());
        }
    }
}
