# BackupX

![Python](https://img.shields.io/badge/Python-3.8%2B-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Type](https://img.shields.io/badge/type-backup_scanner-red.svg)

`BackupX` is a Python-based tool for identifying publicly accessible backup files on web servers. It focuses on common backup file extensions and variations, making it a valuable asset for penetration testers and bug bounty hunters.

---

## ⚙️ Features

- Scans for:
  - `.zip`, `.tar.gz`, `.bak`, `.rar`, `.sql`, `.7z`, etc.
  - Word-based filenames and patterns
- Customizable extension list
- Fast scanning with concise output
- Designed for reconnaissance or audit workflows

---

## 📁 Files

- `backupx.py`: Main script
- (Optional) wordlist file with potential backup file names

---

## 📦 Requirements

- Python 3.8+
- `requests`

Install with:

```bash
pip install requests
```

---

## 🚀 Usage

```bash
python backupx.py -u https://example.com
```

### Optional arguments

| Flag | Description |
|------|-------------|
| `-u`, `--url` | Base URL to scan |
| `-w`, `--wordlist` | Wordlist file (default: internal list) |
| `-e`, `--extensions` | File extensions (e.g., zip, tar.gz, sql) |

---

## 🧪 Example

```bash
python backupx.py -u https://target.com -w words.txt -e zip,sql
```

Output:

```
[+] Found: https://target.com/db_backup_2023.sql [200]
[+] Found: https://target.com/fullsite.zip [200]
```

---

## 🛠 How it Works

1. Loads base URL
2. Combines words and extensions to generate URL candidates
3. Sends HTTP requests and checks for `200 OK` responses
4. Prints accessible backup files

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

## 🙋‍♂️ Author

Developed by eMtwo. Contributions and feedback are welcome!
