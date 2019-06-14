Vytvořte TCP spojení na server fit.cvut.cz, port 443
Znáte z předmětu Počítačové sítě, viz socket, connect
Inicializujte knihovnu OpenSSL (SSL_library_init)
Vytvořte nový kontext (SSL_CTX_new, použijte metodu SSLv23_client_method)
Zakažte zastaralé a děravé protokoly: SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1);
Vytvořte SSL strukturu (SSL_new)
Přiřaďte otevřené spojení (SSL_set_fd)
Zahajte SSL komunikaci (SSL_connect)
Nyní je navázáno SSL spojení na HTTPS server, můžete poslat požadavek

Pošlete HTTP požadavek po zabezpečeném kanálu (SSL_write)
Ve smyčce čtěte odpověď po částech, jak přicházejí po síti, a ukládejte výsledná data do souboru (SSL_read)
Na závěr po sobě uklidíme

Ukončíme SSL session na otevřeném socketu (SSL_shutdown)
Zavřeme socket
Uvolníme strukturu SSL a kontext (SSL_free, SSL_CTX_free)
Nezapomeňte přidat do linkování knihovnu ssl (-lssl).

Přečtení certifikátu ze serveru
Získejte certifikát od serveru (SSL_get_peer_certificate)
a zapište ho do souboru (PEM_write_X509)

Program z minulého cvičení modifikujte, aby vypisoval použitou šifru (SSL_get_current_cipher)
Jméno šifry získáte pomocí (SSL_CIPHER_get_name)
Vysvětlete, co znamenají jednotlivé identifikátory, z kterých se skládá takto získané jméno šifry. Zapište svá zjištění.
Před voláním SSL_connect zakažte konkrétní šifru zjištěnou výše (simulujeme případ, kdy je nalezena zranitelnost šifry a je potřeba ji zakázat), zjistěte, na jaké šifře se dohodne klient a server.
Kdybychom např. chtěli zakázat šifru SEED, napíšeme SSL_set_cipher_list(ssl, "DEFAULT:!SEED");
Vytiskněte všechny šifry, co jsou k dispozici klientovi (SSL_get_cipher_list volejte postupně s prioritami od 0 výše, dokud nevrátí NULL)
Ověřte certifikát serveru
Po vytvoření nového kontextu (SSL_CTX), zavolejte SSL_CTX_load_verify_locations nebo SSL_CTX_set_default_verify_paths (a zkontrolujte výsledek) – tím nastavíte, kde má knihovna hledat kořenové certifikáty.
Po vytvoření SSL spojení (SSL_connect), získejte výsledek verifikace pomocí SSL_get_verify_result a otestujte jej.