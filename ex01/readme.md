

# CSV files
## Comma Separated Values
```
user_id, age, name, address
1,       19,  "Pe sho", "Dolno nanagornisthe", 13
2,       "3,  14","I""van"
3,       20,  Mimi
```

CSV csv = CSV(file, ',')
csv.print();

user_id | age  | name   | address               |
1       | 19   | Pe sho | "Dolno nanagornisthe" | 13
2       | 3.14 | I"van  |                       |
3       | 20   | Mimi   |                       |

Escaping
