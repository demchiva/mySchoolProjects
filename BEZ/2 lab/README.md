1) Najděte libovolnou zprávu, jejíž hash (SHA-256) začíná zleva na posloupnost bajtů 0xAA, 0xBB. Nalezenou zprávu vypište v hexadecimální podobě.

2) Prozkoumejte vliv inicializačního vektoru na šifrový text. Zdůvodněte zjištění.
Modifikujte program tak, aby zašifroval dvě různé zprávy. Zprávy zašifrujte na sobě nezávisle, vždy postupem EVP_EncryptInit(…​), EVP_EncryptUpdate(…​), EVP_EncryptFinal(…​) obě dvě stejným klíčem (což je fatální chyba, jak si později ověříte):
Zvolte si tajný klíč (např. 16 znakový řetězec)
První zpráva bude tajná, 30 znaků dlouhá, její text neprozrazujte
Druhá zpráva bude veřejně známá (prozrazená nebo vynucená) „abcdefghijklmnopqrstuvwxyz0123“
Šifrové texty obou zpráv (v hexadecimální podobě) pošlete svému kolegovi elektronickou poštou, Váš kolega by měl poslat svoji dvojici zpráv Vám. Nezapomeňte ŠT označit, aby bylo zřejmé, který odpovídá veřejně známé zprávě.
Víte následující skutečnosti: Váš kolega byl neopatrný a zašifroval dvě různé zprávy stejným klíčem. Navíc u jedné ze zpráv znáte otevřený text. Vaším úkolem je vyluštit i druhou z obou zpráv. (Postup je triviální.)
Váš program musí přijímat hexadecimální podobu šifrových textů obou zpráv na svém standardním vstupu. Vyluštěnou zprávu vypíše v textové podobě.