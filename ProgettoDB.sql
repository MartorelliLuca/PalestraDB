-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema PROVADB
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema PROVADB
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `PROVADB` ;
USE `PROVADB` ;

-- -----------------------------------------------------
-- Table `PROVADB`.`Utenti`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PROVADB`.`Utenti` (
  `Username` VARCHAR(20) NOT NULL,
  `password` VARCHAR(45) NOT NULL,
  `ruolo` ENUM('segreteria', 'clienti', 'pt') NOT NULL,
  PRIMARY KEY (`Username`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PROVADB`.`PersonalTrainer`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PROVADB`.`PersonalTrainer` (
  `CF` VARCHAR(20) NOT NULL,
  `Nome` VARCHAR(45) NOT NULL,
  `Cognome` VARCHAR(45) NOT NULL,
  `Username` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`CF`),
  INDEX `fk_PersonalTrainer_Utenti1_idx` (`Username` ASC) VISIBLE,
  UNIQUE INDEX `Utenti_Username_UNIQUE` (`Username` ASC) VISIBLE,
  CONSTRAINT `fk_PersonalTrainer_Utenti1`
    FOREIGN KEY (`Username`)
    REFERENCES `PROVADB`.`Utenti` (`Username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PROVADB`.`Clienti`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PROVADB`.`Clienti` (
  `CF` VARCHAR(20) NOT NULL,
  `Nome` VARCHAR(45) NOT NULL,
  `Cognome` VARCHAR(45) NOT NULL,
  `PT` VARCHAR(20) NOT NULL,
  `Username` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`CF`),
  INDEX `fk_Clienti_PersonalTrainer_idx` (`PT` ASC) VISIBLE,
  INDEX `fk_Clienti_Utenti1_idx` (`Username` ASC) VISIBLE,
  UNIQUE INDEX `Utenti_Username_UNIQUE` (`Username` ASC) VISIBLE,
  CONSTRAINT `fk_Clienti_PersonalTrainer`
    FOREIGN KEY (`PT`)
    REFERENCES `PROVADB`.`PersonalTrainer` (`CF`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Clienti_Utenti1`
    FOREIGN KEY (`Username`)
    REFERENCES `PROVADB`.`Utenti` (`Username`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PROVADB`.`Scheda`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PROVADB`.`Scheda` (
  `DataInizio` DATE NOT NULL,
  `DataFine` DATE NULL,
  `Cliente` VARCHAR(20) NOT NULL,
  `Tipo` ENUM('completata', 'non completata') NOT NULL,
  PRIMARY KEY (`DataInizio`, `Cliente`),
  INDEX `fk_Scehda_Clienti1_idx` (`Cliente` ASC) VISIBLE,
  CONSTRAINT `fk_Scehda_Clienti1`
    FOREIGN KEY (`Cliente`)
    REFERENCES `PROVADB`.`Clienti` (`CF`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PROVADB`.`SessioneDiAllenamento`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PROVADB`.`SessioneDiAllenamento` (
  `DataSessione` DATE NOT NULL,
  `OrarioInizio` TIME NOT NULL,
  `OrarioFine` TIME NULL,
  `dataInizioScheda` DATE NOT NULL,
  `Cliente` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`DataSessione`, `dataInizioScheda`, `Cliente`),
  INDEX `fk_SessioneDiAllenamento_Scheda1_idx` (`dataInizioScheda` ASC, `Cliente` ASC) VISIBLE,
  CONSTRAINT `fk_SessioneDiAllenamento_Scheda1`
    FOREIGN KEY (`dataInizioScheda` , `Cliente`)
    REFERENCES `PROVADB`.`Scheda` (`DataInizio` , `Cliente`)
    ON DELETE CASCADE
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PROVADB`.`Esercizi`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PROVADB`.`Esercizi` (
  `Nome` VARCHAR(30) NOT NULL,
  PRIMARY KEY (`Nome`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PROVADB`.`SchedaEsercizi`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PROVADB`.`SchedaEsercizi` (
  `dataInizioScheda` DATE NOT NULL,
  `Cliente` VARCHAR(20) NOT NULL,
  `Esercizio` VARCHAR(30) NOT NULL,
  `Posizione` INT NOT NULL,
  `NumeroRipetizioni` INT NOT NULL,
  `NumeroSerie` INT NOT NULL,
  PRIMARY KEY (`dataInizioScheda`, `Cliente`, `Esercizio`),
  INDEX `fk_Scheda_has_Esercizi_Esercizi1_idx` (`Esercizio` ASC) VISIBLE,
  INDEX `fk_Scheda_has_Esercizi_Scheda1_idx` (`dataInizioScheda` ASC, `Cliente` ASC) VISIBLE,
  CONSTRAINT `fk_Scheda_has_Esercizi_Scheda1`
    FOREIGN KEY (`dataInizioScheda` , `Cliente`)
    REFERENCES `PROVADB`.`Scheda` (`DataInizio` , `Cliente`)
    ON DELETE CASCADE
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Scheda_has_Esercizi_Esercizi1`
    FOREIGN KEY (`Esercizio`)
    REFERENCES `PROVADB`.`Esercizi` (`Nome`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `PROVADB`.`EserciziSvolti`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `PROVADB`.`EserciziSvolti` (
  `Esercizio` VARCHAR(30) NOT NULL,
  `DataSessione` DATE NOT NULL,
  `dataInizioScheda` DATE NOT NULL,
  `Cliente` VARCHAR(20) NOT NULL,
  `SerieCorrente` INT NOT NULL,
  PRIMARY KEY (`Esercizio`, `DataSessione`, `dataInizioScheda`, `Cliente`),
  INDEX `fk_Esercizi_has_SessioneDiAllenamento_SessioneDiAllenamento_idx` (`DataSessione` ASC, `dataInizioScheda` ASC, `Cliente` ASC) VISIBLE,
  INDEX `fk_Esercizi_has_SessioneDiAllenamento_Esercizi1_idx` (`Esercizio` ASC) VISIBLE,
  CONSTRAINT `fk_Esercizi_has_SessioneDiAllenamento_Esercizi1`
    FOREIGN KEY (`Esercizio`)
    REFERENCES `PROVADB`.`Esercizi` (`Nome`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Esercizi_has_SessioneDiAllenamento_SessioneDiAllenamento1`
    FOREIGN KEY (`DataSessione` , `dataInizioScheda` , `Cliente`)
    REFERENCES `PROVADB`.`SessioneDiAllenamento` (`DataSessione` , `dataInizioScheda` , `Cliente`)
    ON DELETE CASCADE
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

USE `PROVADB` ;

-- -----------------------------------------------------
-- procedure aggiungi_cliente
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_cliente`(
	in var_codiceFiscale VARCHAR(20),
	in var_nome VARCHAR(45),
	in var_cognome VARCHAR(45),
	in var_username VARCHAR(20),
    in var_pass VARCHAR (45))
BEGIN
	
	declare var_PT VARCHAR(20);
	declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;
    
    IF (PROVADB.check_cf(var_codiceFiscale) is FALSE) THEN 
		signal sqlstate '45009' set message_text = 'CODICE FISCALE NON VALIDO';
	END IF;
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
	START TRANSACTION ;

		-- Selezione PT con meno clienti
		SELECT PersonalTrainer.CF into var_PT
		FROM PersonalTrainer
		LEFT JOIN Clienti ON PersonalTrainer.CF = Clienti.PT
		GROUP BY PersonalTrainer.CF
		ORDER BY COUNT(Clienti.PT) ASC
		LIMIT 1;
    
		insert into `Utenti` (`Username`, `password`, `ruolo`)
		values (var_username, sha1(var_pass), 'clienti');
    
		-- Aggiungo Cliente
		insert into `Clienti` (`CF`, `Nome`, `Cognome`, `Username`, `PT`)
		values (var_codiceFiscale, var_nome, var_cognome, var_username, var_PT);
    
    COMMIT;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_serie_esercizio
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_serie_esercizio`(in var_nomeEsercizio varchar(30), 
	in var_dataSessione date, 
	in var_dataInizioScheda date, 
	in var_cfClienti varchar(20),
	in var_serieCorrente int)
BEGIN
	
    declare var_serieAggiornata int;
    declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;

	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
	START TRANSACTION ;

		set var_serieAggiornata = var_seriecorrente + 1;
        
		UPDATE EserciziSvolti
		SET  SerieCorrente = var_serieAggiornata
		WHERE Cliente = var_cfClienti
			AND  dataInizioScheda = var_dataInizioScheda
			AND Esercizio = var_nomeEsercizio
			AND dataSessione = var_dataSessione;
	
    COMMIT;

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_serie_mancanti
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `visualizza_serie_mancanti`(in var_cfCliente varchar(20),
	in var_nomeEsercizio varchar(30), 
	in var_dataSessione date, 
	in var_dataInizioScheda date)
BEGIN

	SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
	start transaction;
    
		SELECT es.Esercizio, (NumeroSerie-SerieCorrente) as SerieMancanti 
		FROM EserciziSvolti es join SchedaEsercizi se ON es.Cliente = se.Cliente 
			AND es.dataInizioScheda = se.dataInizioScheda
			AND es.Esercizio = se.Esercizio
		WHERE es.Cliente = var_cfCliente
			AND es.dataInizioScheda = var_dataInizioScheda
            AND es.DataSessione = var_dataSessione
            AND es.Esercizio = var_nomeEsercizio;
            
	commit ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_schede_archiviate
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `visualizza_schede_archiviate`(in var_cfClienti varchar(20), out var_numSchede int)
BEGIN
    declare exit handler for sqlexception
	begin 
		rollback;
		resignal;
	end;
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
    start transaction;
		
        SELECT count(*) into var_numSchede
        FROM Scheda
        WHERE DataFine is not NULL and Cliente = var_cfClienti
		ORDER BY DataInizio ASC;
        
        IF(var_numSchede = 0) THEN
			signal sqlstate '45025' set message_text = 'NON HAI SCHEDE ARCHIVIATE';
        END IF;
		
		SELECT DataInizio, DataFine
        FROM Scheda
        WHERE DataFine is not NULL and Cliente = var_cfClienti
		ORDER BY DataInizio ASC;
        
	commit ;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_scheda_attiva
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `visualizza_scheda_attiva`(in var_cfClienti varchar(20))
BEGIN
	declare var_Dat date;
    declare exit handler for sqlexception
	begin 
		rollback;
		resignal;
	end;
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
    start transaction;

		SELECT DataInizio INTO var_Dat
		FROM Scheda
		WHERE DataFine IS NULL AND Cliente = var_cfClienti;

		IF var_Dat IS NULL THEN
			SIGNAL SQLSTATE '45024' SET MESSAGE_TEXT = 'SCHEDA ATTIVA INESISTENTE';
		END IF;

        SELECT Posizione, Esercizio, NumeroSerie as Serie, NumeroRipetizioni as Ripetizioni
        FROM SchedaEsercizi
        WHERE Cliente = var_cfClienti and dataInizioScheda = var_Dat
        order by Posizione;
        
	commit ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_esercizi_mancanti
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `visualizza_esercizi_mancanti`(in var_cfCliente varchar(20),
	in var_dataSessione date, 
	in var_dataInizioScheda date)
BEGIN

	SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
	start transaction;
    
		SELECT Posizione, Esercizio, NumeroSerie as Serie, NumeroRipetizioni as Ripetizioni
		FROM SchedaEsercizi se
		WHERE Cliente = var_cfCliente
			AND dataInizioScheda = var_dataInizioScheda
			AND Esercizio not in (SELECT Esercizio
									FROM EserciziSvolti es
									WHERE es.Cliente = var_cfCliente
										AND DataSessione = var_dataSessione
										AND es.dataInizioScheda = var_dataInizioScheda)
		ORDER BY Posizione;
                                        
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure termina_sessione
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `termina_sessione`(in var_dataSessione date, 
	in var_OrarioInizio time,
    in var_dataInizioScheda date,
    in var_cfClienti varchar(20))
BEGIN
	
    declare var_time time;
	set var_time = curtime();
	
	UPDATE SessioneDiAllenamento
	SET  OrarioFine = var_time
	WHERE Cliente = var_cfClienti
		AND  dataInizioScheda = var_dataInizioScheda
		AND OrarioInizio = var_OrarioInizio
		AND dataSessione = var_dataSessione;
        
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_clienti
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `visualizza_clienti`(in var_cfPT VARCHAR(20))
BEGIN

	SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
    start transaction;

		SELECT CF, Nome, Cognome
		FROM Clienti
		WHERE PT = var_cfPT;
	
    commit;

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure scegli_scheda_archiviata
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `scegli_scheda_archiviata`(IN var_CF_Cliente VARCHAR(20), IN var_dataInizioScheda DATE)
BEGIN

    DECLARE numEsercizi INT;
	declare exit handler for sqlexception
	begin 
		rollback;
		resignal;
	end;
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
    START TRANSACTION;
		SELECT COUNT(*) INTO numEsercizi
		FROM Scheda s
		JOIN SchedaEsercizi se ON s.DataInizio = se.DataInizioScheda AND s.Cliente = se.Cliente
		WHERE s.Cliente = var_CF_Cliente AND s.DataInizio = var_dataInizioScheda;

		IF numEsercizi = 0 THEN
			signal sqlstate '45021' set message_text = 'DATA NON NEL DATABASE';
		ELSE
			SELECT Posizione, Esercizio, NumeroSerie as Serie, NumeroRipetizioni as Ripetizioni
			FROM Scheda s
			JOIN SchedaEsercizi se ON s.DataInizio = se.DataInizioScheda AND s.Cliente = se.Cliente
			WHERE s.Cliente = var_CF_Cliente AND s.DataInizio = var_dataInizioScheda
			ORDER BY Posizione;
		END IF;
	COMMIT;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure login
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `login`(
	IN var_username VARCHAR(15), 
	IN var_password VARCHAR(20), 
    OUT var_role INT)
BEGIN

	DECLARE var_enum_role ENUM("pt","segreteria","clienti") ;
    
	SELECT `Ruolo` 
    FROM `Utenti`
    WHERE `Username` = var_username AND `Password` = SHA1(var_password)
    INTO var_enum_role ;
    
    IF var_enum_role = "pt" THEN
		SET var_role = 0 ;
	ELSEIF var_enum_role = "segreteria" THEN
		SET var_role = 1 ;
	ELSEIF var_enum_role = "clienti" THEN
		SET var_role = 2 ;
	ELSE
		SET var_role = 3 ;
	END IF ;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_esercizio
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `inserisci_esercizio`(
    IN var_cliente VARCHAR(20),
    IN var_esercizio VARCHAR(30),
    IN var_numeroRipetizioni INT,
    IN var_numeroSerie INT,
    IN var_posizione INT,
    IN var_dataInizioScheda DATE
)
BEGIN
	declare var int;
    declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED; 
	start transaction;
		SELECT COUNT(*) INTO var
		FROM Scheda
		WHERE Cliente = var_cliente AND DataInizio = var_dataInizioScheda AND Tipo = 'completata' and DataFine is NULL;

        IF (var = 1) THEN
			signal sqlstate '45000' set message_text = 'NON PUOI INSERIRE ESERCIZI DENTRO SCHEDE GIA\' COMPLETATE';
        ELSE 
			insert into `SchedaEsercizi` (`dataInizioScheda`, `Cliente`, `Esercizio`, `Posizione`, `NumeroRipetizioni`, `NumeroSerie`)
			values (var_dataInizioScheda, var_cliente, var_esercizio, var_posizione, var_numeroRipetizioni, var_numeroSerie);
		END IF;
    commit;

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure genera_report
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `genera_report`(IN var_trainer_cf VARCHAR(20), IN var_dataInizio DATE, IN var_dataFine DATE)
BEGIN

	declare exit handler for sqlexception ## Dichiarazione Gestore eccezione sollevata dal Trigger
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;
    
	DROP TABLE IF EXISTS report_temp;
		
	-- Crea una tabella temporanea per il report
	CREATE TEMPORARY TABLE report_temp (
	CF VARCHAR(20),
	Nome VARCHAR(45),
	Cognome VARCHAR(45),
	DataScheda DATE,
	Sessione DATE,
	Completamento VARCHAR(10),
	Durata CHAR(10));
	
        
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
	START TRANSACTION;
        
		-- Inserisci i dati nel report temporaneo
		INSERT INTO report_temp (CF, Nome, Cognome, DataScheda, Sessione, Completamento, Durata)
		SELECT c.CF as CF, c.Nome as Nome, c.Cognome as Cognome, sa.DataInizio as DataScheda, ses.DataSessione as Sessione,
			CONCAT(IFNULL((SUM(esv.SerieCorrente) / SUM(es.NumeroSerie)) * 100, 0), '%') AS Completamento,
			CAST(TIMEDIFF(ses.OrarioFine, ses.OrarioInizio) AS CHAR(10)) AS Durata
		FROM Clienti c
			JOIN Scheda sa ON c.CF = sa.Cliente
			JOIN SessioneDiAllenamento ses ON sa.Cliente = ses.Cliente 
				AND sa.DataInizio = ses.dataInizioScheda
			JOIN SchedaEsercizi es ON sa.Cliente = es.Cliente 
				AND sa.DataInizio = es.dataInizioScheda
			LEFT JOIN EserciziSvolti esv ON ses.Cliente = esv.Cliente 
				AND ses.dataInizioScheda = esv.dataInizioScheda 
				AND ses.DataSessione = esv.dataSessione 
				AND es.Esercizio = esv.Esercizio
		WHERE c.PT = var_trainer_cf and OrarioFine is not NULL
			AND ses.DataSessione BETWEEN var_dataInizio AND var_dataFine
		GROUP BY c.CF, c.Nome, c.Cognome, ses.DataSessione, sa.DataInizio;

		-- Seleziona i dati dal report temporaneo per visualizzarli
		SELECT *
		FROM report_temp;
	
    COMMIT;

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inizia_sessione
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `inizia_sessione`(in var_cfClienti varchar(20),
	out var_dataInizioScheda date,
	out var_oggi date,
	out var_ora time)
BEGIN
   
    declare var_tipo varchar(15);
    
    declare exit handler for sqlexception
	begin 
		rollback;
		resignal;
	end;
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
    START TRANSACTION;
    
		SELECT DataInizio, Tipo INTO var_dataInizioScheda, var_tipo
		FROM Scheda
		WHERE DataFine IS NULL AND Cliente = var_cfClienti;

		if(var_tipo = 'non completata') then
			signal sqlstate '45001' set message_text = 'NON PUOI INIZIARE UNA SESSIONE: LA SCHEDA NON E\' ANCORA PRONTA.';
		END IF;
		
        set var_oggi = curdate();
		set var_ora = curtime();
        
		insert into `SessioneDiAllenamento` (`dataSessione`, `OrarioInizio`, `OrarioFine`, `dataInizioScheda`, `Cliente`)
        values (var_oggi, var_ora, NULL, var_dataInizioScheda, var_cfClienti);
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure crea_nuova_scheda
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `crea_nuova_scheda`(
	in var_cfCliente VARCHAR(20),
	in var_cfPt VARCHAR(20),
    out var_dataInizio date)
BEGIN
	
    declare var_Pt VARCHAR(20);
    
	DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        ROLLBACK;
        RESIGNAL;
    END;
    
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
    START TRANSACTION;		
		IF (PROVADB.check_cf(var_cfCliente) is FALSE) THEN 
			signal sqlstate '45015' set message_text = 'CODICE FISCALE NON VALIDO';
		END IF;
	
		SELECT PT INTO var_Pt
		FROM Clienti
		WHERE CF = var_cfCliente;
        
        IF (var_Pt <> var_cfPt) THEN 
			signal sqlstate '45016' set message_text = 'NON PUOI CREARGLI LA SCHEDA, NON E\' UN TUO CLIENTE.';
		END IF;
        
		set var_dataInizio = curdate();
		
		INSERT INTO `Scheda` (`DataInizio`, `Cliente`, `Tipo`)
		values (var_dataInizio, var_cfCliente, 'non completata');
	
    COMMIT;
	
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure esegui_esercizio
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `esegui_esercizio`(in var_nomeEsercizio varchar(30), 
	in var_dataSessione date, 
	in var_dataInizioScheda date,
	in var_cfClienti varchar(20))
BEGIN
	declare exit handler for sqlexception 
    begin
        rollback; ## Annullamento Transazione
        resignal; ## Ridirezione Segnale al Client
    end;

	insert into `EserciziSvolti` (`Esercizio`, `DataSessione`, `dataInizioScheda`, `Cliente`, `SerieCorrente`)
	values (var_nomeEsercizio, var_dataSessione, var_dataInizioScheda, var_cfClienti, 1);

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure archivia_scheda
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `archivia_scheda`(
    IN var_cfCliente VARCHAR(20),
    IN var_cfPt VARCHAR(20)
)
BEGIN
    DECLARE var_dataFine DATE;
    DECLARE var_dataInizio DATE;
    DECLARE var_sessioneStato INT;
    DECLARE var_Pt VARCHAR(20);
    
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        ROLLBACK;
        RESIGNAL;
    END;
    
    -- Imposta il livello di isolamento appropriato per la transazione
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED; 	
    START TRANSACTION;									
    
		 IF (PROVADB.check_cf(var_cfCliente) is FALSE) THEN 
			signal sqlstate '45011' set message_text = 'CODICE FISCALE NON VALIDO';
		END IF;
        
		SELECT PT INTO var_Pt
		FROM Clienti
		WHERE CF = var_cfCliente;
        
        IF (var_Pt <> var_cfPt) THEN 
			signal sqlstate '45012' set message_text = 'NON PUOI ARCHIVIARE LA SUA SCHEDA, NON E\' UN TUO CLIENTE.';
		END IF;
        
        -- Ottenere la data di inizio della scheda attiva per il cliente
		SELECT DataInizio INTO var_dataInizio
		FROM Scheda join Clienti on Cliente = CF
		WHERE Cliente = var_cfCliente AND DataFine IS NULL;
        
        IF (var_dataInizio is NULL) THEN 
			signal sqlstate '45013' set message_text = 'Il cliente selezionato non ha una scheda attiva.';
		END IF;

        -- La sessione di allenamento non è iniziata, si può procedere con l'archiviazione della scheda
        SET var_dataFine = CURDATE();

		IF (PROVADB.check_init_session(var_cfCliente, var_dataInizio) = 1) THEN 
			signal sqlstate '45014' set message_text = 'ATTENZIONE L\'UTENTE IN QUESTIONE STA ESEGUENDO UNA SESSIONE CON LA SCHEDA CHE VUOI ARCHIVIARE: ASPETTA CHE FINISCA.';
		END IF;
        
        UPDATE Scheda
        SET DataFine = var_dataFine
        WHERE Cliente = var_cfCliente AND DataFine IS NULL;
        
	COMMIT;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- function check_cf
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` FUNCTION `check_cf`(CF VARCHAR(20)) RETURNS tinyint(1)
    DETERMINISTIC
BEGIN
    
    IF CF REGEXP '^[A-Z]{6}[0-9]{2}[A-Z][0-9]{2}[A-Z][0-9]{3}[A-Z]$' THEN
        RETURN TRUE;
    ELSE
        RETURN FALSE;
    END IF;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- function check_init_session
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` FUNCTION `check_init_session`(CF VARCHAR(20), dataInitScheda date) RETURNS int
    DETERMINISTIC
BEGIN
	declare var_result INT;
	
	IF EXISTS (
		SELECT 1
		FROM SessioneDiAllenamento
		WHERE Cliente = CF
			AND dataInizioScheda = dataInitScheda
			AND OrarioInizio IS NOT NULL
			AND OrarioFine IS NULL
	) THEN
		SET var_result = 1; -- 1 = Sessione Iniziata ma non finita
	ELSEIF EXISTS (
		SELECT 1
		FROM SessioneDiAllenamento
		WHERE Cliente = CF
			AND dataInizioScheda = dataInitScheda
			AND OrarioInizio IS NOT NULL
			AND OrarioFine IS NOT NULL
	) THEN 
		SET var_result = 2; -- 2 = Sessione Iniziata e Finita
	ELSE
		SET var_result = 3; -- 3 = Sessione non iniziata
	END IF;
	RETURN var_result;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_pt
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `aggiungi_pt`(
	in var_codiceFiscale VARCHAR(20),
	in var_nome VARCHAR(45),
	in var_cognome VARCHAR(45),
	in var_username VARCHAR(20),
    in var_pass VARCHAR (45))
BEGIN

	IF (PROVADB.check_cf(var_codiceFiscale) is FALSE) THEN 
		signal sqlstate '45010' set message_text = 'CODICE FISCALE PT NON VALIDO';
	END IF;
	
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
	START TRANSACTION ;
		insert into `Utenti` (`Username`, `password`, `ruolo`)
		values (var_username, sha1(var_pass), 'pt');

		insert into `PersonalTrainer` (`CF`, `Nome`, `Cognome`, `Username`)
		values (var_codiceFiscale, var_nome, var_cognome, var_username);
	COMMIT;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure scheda_completata
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `scheda_completata`(IN var_cfCliente VARCHAR(20), in var_dataInizioScheda date)
BEGIN
	UPDATE Scheda
    SET Tipo = 'completata'
    WHERE DataFine is NULL AND Cliente = var_cfCliente;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure prendi_cliente_cf
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `prendi_cliente_cf`(in var_username varchar(20), out var_cf varchar(20))
BEGIN
	
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
	START TRANSACTION ;
    
		SELECT CF into var_cf
		FROM Clienti 
		WHERE Username = var_username;
	
    COMMIT;
    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure prendi_pt_cf
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `prendi_pt_cf`(in var_username varchar(20), out var_cf varchar(20))
BEGIN
	
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED ;
	START TRANSACTION ;

	SELECT CF into var_cf
	FROM PersonalTrainer 
	WHERE Username = var_username;

	COMMIT;

END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure recupera_dati_sessione
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `recupera_dati_sessione`(IN var_cliente VARCHAR(20),
	OUT var_dataSessione date,
	OUT var_dataInizioScheda date,
    OUT var_orarioInizio TIME)
BEGIN
    DECLARE num_sessioni INT;
	declare exit handler for sqlexception
	begin 
		rollback;
		resignal;
	end;
	
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
    START TRANSACTION;
    
		SELECT COUNT(*) INTO num_sessioni
		FROM SessioneDiAllenamento
		WHERE Cliente = var_cliente 
			AND DataSessione = CURDATE()
			AND OrarioInizio IS NOT NULL
			AND OrarioFine IS NULL;

		IF num_sessioni > 0 THEN
			SELECT DataInizio INTO var_dataInizioScheda
			FROM Scheda
			WHERE DataFine IS NULL AND Cliente = var_cliente;

			set var_dataSessione = curdate();
    
			SELECT OrarioInizio into var_orarioInizio
			FROM SessioneDiAllenamento
			WHERE Cliente = var_cliente 
				AND OrarioFine is null
				AND dataInizioScheda = var_dataInizioScheda
				AND DataSessione = var_dataSessione;

		ELSE
			signal sqlstate '45020' set message_text = 'IMPOSSIBILE RECUPERARE LA SESSIONE DI ALLENAMENTO: SI POSSONO RECUPERARE SOLO SESSIONI INIZIATE MA NON FINITE';
		END IF;
	COMMIT;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure pt_visualizza_scheda_attiva
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `pt_visualizza_scheda_attiva`(in var_cfClienti varchar(20), in var_pt varchar(20))
BEGIN
	declare var_Dat date;
    declare var_num INT;
    declare exit handler for sqlexception
	begin 
		rollback;
		resignal;
	end;
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
    start transaction;
		
        IF (PROVADB.check_cf(var_cfClienti) is FALSE) THEN 
			signal sqlstate '45017' set message_text = 'CODICE FISCALE NON VALIDO';
		END IF;
        
		SELECT count(*) INTO var_num
		FROM Clienti
		WHERE PT = var_pt AND CF = var_cfClienti;

		IF (var_num = 0) THEN 
			signal sqlstate '45018' set message_text = 'NON E\' UN TUO CLIENTE, MI SPIACE MA NON PUOI VEDERE LA SUA SCHEDA ATTIVA';
		END IF;
        
		SELECT DataInizio INTO var_Dat
		FROM Scheda
		WHERE DataFine IS NULL AND Cliente = var_cfClienti;

		IF var_Dat IS NULL THEN
			SIGNAL SQLSTATE '45019' SET MESSAGE_TEXT = 'SCHEDA ATTIVA INESISTENTE';
		END IF;

        SELECT Posizione, Esercizio, NumeroSerie as Serie, NumeroRipetizioni as Ripetizioni
        FROM SchedaEsercizi
        WHERE Cliente = var_cfClienti and dataInizioScheda = var_Dat
        order by Posizione;
        
	commit ;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure scegli_scheda_attiva_non_completa
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `scegli_scheda_attiva_non_completa`(IN var_CF_Cliente VARCHAR(20),
	out var_dataInizioScheda DATE,
    out var_Position int)
BEGIN

    DECLARE num INT;
	declare exit handler for sqlexception
	begin 
		rollback;
		resignal;
	end;
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
    START TRANSACTION;
		IF (PROVADB.check_cf(var_CF_Cliente) is FALSE) THEN 
			signal sqlstate '45022' set message_text = 'CODICE FISCALE NON VALIDO';
		END IF;
    
		SELECT DataInizio INTO var_dataInizioScheda
		FROM Scheda 
		WHERE Cliente = var_CF_Cliente AND DataFine is NULL;
		
		IF (var_dataInizioScheda IS NULL) THEN
			signal sqlstate '45023' set message_text = 'IL CLIENTE SELEZIONATO NON HA PROPRIO UNA SCHEDA ATTIVA';
		END IF;
	
		SELECT max(Posizione) into var_Position
		FROM SchedaEsercizi
		WHERE Cliente = var_CF_Cliente AND dataInizioScheda = var_dataInizioScheda;

		SELECT Posizione, Esercizio, NumeroSerie as Serie, NumeroRipetizioni as Ripetizioni
		FROM Scheda s
			JOIN SchedaEsercizi se ON s.DataInizio = se.DataInizioScheda AND s.Cliente = se.Cliente
		WHERE s.Cliente = var_CF_Cliente AND s.DataInizio = var_dataInizioScheda AND Tipo = 'non completata'
		ORDER BY Posizione;
    COMMIT;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_schede_non_completate
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `visualizza_schede_non_completate`(IN var_PT VARCHAR(20))
BEGIN
	declare num int;
	
	declare exit handler for sqlexception
	begin 
		rollback;
		resignal;
	end;
    
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
    START TRANSACTION;

		SELECT count(*) into num
		FROM Scheda s join Clienti on s.Cliente = CF
		WHERE PT = var_PT AND Tipo = 'non completata' AND DataFine is null;
		
		IF(num = 0) THEN
			signal sqlstate '45026' set message_text = 'NON HAI SCHEDE DA MODIFICARE, SONO TUTTE COMPLETATE';
		END IF;
    
		SELECT Nome, Cognome, s.Cliente, s.DataInizio
		FROM Scheda s join Clienti on s.Cliente = CF
		WHERE PT = var_PT AND Tipo = 'non completata'
		ORDER BY DataInizio;
        
	COMMIT;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_esercizio_in_palestra
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE PROCEDURE `aggiungi_esercizio_in_palestra` (in var_esercizio varchar(30))
BEGIN
	insert into `Esercizi` (`Nome`)
	values (var_esercizio);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_esercizi
-- -----------------------------------------------------

DELIMITER $$
USE `PROVADB`$$
CREATE PROCEDURE `visualizza_esercizi` ()
BEGIN
	
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
    START TRANSACTION;
    
		SELECT Nome
		FROM Esercizi;
	
    COMMIT;
END$$

DELIMITER ;
USE `PROVADB`;

DELIMITER $$
USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` TRIGGER `Scheda_BEFORE_INSERT` BEFORE INSERT ON `Scheda` FOR EACH ROW BEGIN
    -- Dichiarazione delle variabili
    DECLARE var_count INT;

    -- Verifica se esistono altre tuple per lo stesso cliente con DataFine NULL
    SELECT COUNT(*) INTO var_count
    FROM Scheda
    WHERE Cliente = NEW.Cliente AND DataFine IS NULL;

    -- Se esistono tuple con DataFine NULL, genera un errore
    IF var_count > 0 THEN
        SIGNAL SQLSTATE '45004' SET MESSAGE_TEXT = 'Esiste già una scheda attiva per questo cliente.';
    END IF;
END$$

USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` TRIGGER `before_update_scheda` BEFORE UPDATE ON `Scheda` FOR EACH ROW BEGIN
    IF New.Tipo = 'non completata' THEN
        SIGNAL SQLSTATE '45005' SET MESSAGE_TEXT = 'La scheda deve essere completa prima di essere archiviata.';
    END IF;
END$$

USE `PROVADB`$$
CREATE DEFINER = CURRENT_USER TRIGGER `PROVADB`.`SessioneDiAllenamento_BEFORE_INSERT` BEFORE INSERT ON `SessioneDiAllenamento` FOR EACH ROW
BEGIN
	IF HOUR(CURRENT_TIME()) < 7 OR HOUR(CURRENT_TIME()) > 23 THEN
        SIGNAL SQLSTATE '45007'
        SET MESSAGE_TEXT = 'Puoi iniziare una sessione solo tra le 7:00 e le 23:00';
    END IF;
END$$

USE `PROVADB`$$
CREATE DEFINER = CURRENT_USER TRIGGER `PROVADB`.`SessioneDiAllenamento_BEFORE_UPDATE` BEFORE UPDATE ON `SessioneDiAllenamento` FOR EACH ROW
BEGIN
	IF HOUR(CURRENT_TIME()) < 7 OR HOUR(CURRENT_TIME()) > 23 THEN
        SIGNAL SQLSTATE '45008'
        SET MESSAGE_TEXT = 'Puoi chiudere una sessione solo tra le 7:00 e le 23:00';
    END IF;
END$$

USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` TRIGGER `SchedaEsercizi_BEFORE_INSERT` BEFORE INSERT ON `SchedaEsercizi` FOR EACH ROW BEGIN
   DECLARE position_count INT;

    -- Controlla se esiste un esercizio con la stessa posizione e dataInizioScheda
    SELECT COUNT(*) INTO position_count
    FROM SchedaEsercizi
    WHERE dataInizioScheda = NEW.dataInizioScheda
        AND Posizione = NEW.Posizione
        AND Cliente = NEW.Cliente;

    -- Se esiste un esercizio con la stessa posizione, genera un errore
    IF position_count > 0 THEN
        SIGNAL SQLSTATE '45006'
        SET MESSAGE_TEXT = 'Esiste già un esercizio con la stessa posizione in questa scheda.';
    END IF;
END$$

USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` TRIGGER `check_eserciziSvolti_insert` BEFORE INSERT ON `EserciziSvolti` FOR EACH ROW BEGIN
     DECLARE esercizio_count INT;
    
    -- Controlla se l'esercizio esiste nella tabella SchedaEsercizi
    SELECT COUNT(*) INTO esercizio_count
    FROM SchedaEsercizi
    WHERE Cliente = NEW.Cliente
        AND dataInizioScheda = NEW.dataInizioScheda
        AND Esercizio = NEW.Esercizio;

    -- Se l'esercizio non esiste, genera un errore
    IF esercizio_count = 0 THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'L\'esercizio non esiste nella scheda.';
    END IF;
END$$

USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` TRIGGER `check_eserciziSvolti_orarioInsert` BEFORE INSERT ON `EserciziSvolti` FOR EACH ROW
BEGIN
    IF HOUR(CURRENT_TIME()) < 7 OR HOUR(CURRENT_TIME()) > 23 THEN
        SIGNAL SQLSTATE '45001'
        SET MESSAGE_TEXT = 'L\'orario di inserimento deve essere compreso tra le 7:00 e le 23:00';
    END IF;
END;$$

USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` TRIGGER `before_update_esercizisvolti` BEFORE UPDATE ON `EserciziSvolti` FOR EACH ROW BEGIN
    DECLARE num_serie INT;

    -- Ottieni il numero di serie dall'esercizischeda
    SELECT NumeroSerie INTO num_serie
    FROM SchedaEsercizi
    WHERE Esercizio = NEW.Esercizio
    AND dataInizioScheda = NEW.dataInizioScheda
    AND Cliente = NEW.Cliente;

    -- Verifica se la serie corrente è maggiore del numero di serie
    IF NEW.SerieCorrente > num_serie THEN
        SIGNAL SQLSTATE '45002'
            SET MESSAGE_TEXT = 'La serie corrente è maggiore del numero di serie consentito.';
    END IF;
END$$

USE `PROVADB`$$
CREATE DEFINER=`root`@`localhost` TRIGGER `check_eserciziSvolti_orarioUpdate` BEFORE UPDATE ON `EserciziSvolti` FOR EACH ROW
BEGIN
	IF HOUR(CURRENT_TIME()) < 7 OR HOUR(CURRENT_TIME()) > 23 THEN
        SIGNAL SQLSTATE '45003'
        SET MESSAGE_TEXT = 'L\'orario di aggiornamento deve essere compreso tra le 7:00 e le 23:00';
    END IF;
END;$$


DELIMITER ;
CREATE USER 'clienti' IDENTIFIED BY 'Clienti!123';

CREATE USER 'pt' IDENTIFIED BY 'Pt@12345';

CREATE USER 'segreteria' IDENTIFIED BY 'Segreteria@12345';

CREATE USER 'utenti' IDENTIFIED BY 'Utenti@12345';


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Data for table `PROVADB`.`Utenti`
-- -----------------------------------------------------
START TRANSACTION;
USE `PROVADB`;
INSERT INTO `PROVADB`.`Utenti` (`Username`, `password`, `ruolo`) VALUES ('segreteria', '02cad8ee4fb1cc60f6a485316007c9d709293cbd', 'segreteria');

COMMIT;

