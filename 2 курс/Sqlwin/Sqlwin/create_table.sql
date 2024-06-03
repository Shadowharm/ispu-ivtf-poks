--DROP SCHEMA public CASCADE;
--CREATE SCHEMA public;

-- Create the Employer table if it does not exist
CREATE TABLE IF NOT EXISTS Employer (
    Employer_ID SERIAL PRIMARY KEY,
    Company_Name VARCHAR(255) NOT NULL,
    Contact_Person VARCHAR(255) NOT NULL,
    Contact_Phone VARCHAR(20) NOT NULL,
    Address TEXT NOT NULL
);

-- Create the Vacancy table if it does not exist
CREATE TABLE IF NOT EXISTS Vacancy (
    Vacancy_ID SERIAL PRIMARY KEY,
    Number_of_Vacancies INTEGER NOT NULL,
    Position VARCHAR(255) NOT NULL,
    Salary NUMERIC(10, 2) NOT NULL,
    Requirements TEXT NOT NULL,
    Employer_ID INTEGER NOT NULL,
    FOREIGN KEY (Employer_ID) REFERENCES Employer(Employer_ID)
);

-- Create the Applicant table if it does not exist
CREATE TABLE IF NOT EXISTS Applicant (
    Applicant_ID SERIAL PRIMARY KEY,
    Full_Name VARCHAR(255) NOT NULL,
    Birth_Date DATE NOT NULL,
    Education VARCHAR(255) NOT NULL,
    Experience INTEGER NOT NULL,
    Last_Job VARCHAR(255),
    Last_Position INTEGER,
    Dismissal_Reason VARCHAR(255),
    Application_Date DATE NOT NULL,
    FOREIGN KEY (Last_Position) REFERENCES Post(id)
);

CREATE TABLE if NOT EXISTS Post (
    id serial PRIMARY KEY,
    name TEXT
);

-- Create the Employment table if it does not exist
CREATE TABLE IF NOT EXISTS Employment (
    Employment_ID SERIAL PRIMARY KEY,
    Start_Date DATE NOT NULL,
    Applicant_ID INTEGER NOT NULL,
    Vacancy_ID INTEGER NOT NULL,
    FOREIGN KEY (Applicant_ID) REFERENCES Applicant(Applicant_ID),
    FOREIGN KEY (Vacancy_ID) REFERENCES Vacancy(Vacancy_ID)
);

-- Insert data into the Employer table
INSERT INTO Employer (Company_Name, Contact_Person, Contact_Phone, Address) VALUES
('Tech Solutions Ltd.', 'John Doe', '555-1234', '123 Main St, Springfield'),
('Creative Design Studio', 'Jane Smith', '555-5678', '456 Elm St, Springfield'),
('Global IT Services', 'Robert Brown', '555-9101', '789 Maple St, Springfield'),
('Finance Experts Inc.', 'Emily Johnson', '555-1122', '101 Oak St, Springfield'),
('HealthCare Co.', 'Michael White', '555-3344', '202 Pine St, Springfield'),
('EduSmart Ltd.', 'Sarah Green', '555-5566', '303 Cedar St, Springfield'),
('Retail Kings', 'David Black', '555-7788', '404 Birch St, Springfield'),
('Construction Giants', 'Linda Adams', '555-9900', '505 Walnut St, Springfield'),
('Automotive World', 'James Scott', '555-2233', '606 Chestnut St, Springfield'),
('Travel Adventures', 'Patricia Miller', '555-4455', '707 Ash St, Springfield');

-- Insert data into the Post table
INSERT INTO Post (name) VALUES
('Software Developer'),
('Graphic Designer'),
('Network Engineer'),
('Financial Analyst'),
('Nurse'),
('Teacher'),
('Store Manager'),
('Civil Engineer'),
('Automotive Technician'),
('Travel Agent');

-- Insert data into the Vacancy table
INSERT INTO Vacancy (Number_of_Vacancies, Position, Salary, Requirements, Employer_ID) VALUES
(3, 'Software Developer', 60000, 'BSc in Computer Science, 3+ years of experience', 1),
(2, 'Graphic Designer', 45000, 'BSc in Design, 2+ years of experience', 2),
(5, 'Network Engineer', 55000, 'BSc in Information Technology, 4+ years of experience', 3),
(1, 'Financial Analyst', 65000, 'BSc in Finance, 5+ years of experience', 4),
(4, 'Nurse', 50000, 'BSc in Nursing, 2+ years of experience', 5),
(2, 'Teacher', 40000, 'BEd, 3+ years of experience', 6),
(3, 'Store Manager', 48000, 'BSc in Business Administration, 4+ years of experience', 7),
(1, 'Civil Engineer', 70000, 'BSc in Civil Engineering, 6+ years of experience', 8),
(2, 'Automotive Technician', 45000, 'Diploma in Automotive Technology, 3+ years of experience', 9),
(3, 'Travel Agent', 40000, 'Diploma in Travel and Tourism, 2+ years of experience', 10);

-- Insert data into the Applicant table
INSERT INTO Applicant (Full_Name, Birth_Date, Education, Experience, Last_Job, Last_Position, Dismissal_Reason, Application_Date) VALUES
('Alex Johnson', '1990-05-14', 'BSc in Computer Science', 5, 'Tech Corp', 1, 'Career Growth', '2024-01-15'),
('Jessica Brown', '1985-11-23', 'BSc in Design', 7, 'Design Studio', 2, 'Relocation', '2024-02-20'),
('William Smith', '1992-07-30', 'BSc in Information Technology', 4, 'Net Solutions', 3, 'Better Opportunity', '2024-03-10'),
('Emma Wilson', '1988-02-17', 'BSc in Finance', 6, 'Finance Group', 4, 'Career Change', '2024-04-05'),
('Daniel Lee', '1995-09-09', 'BSc in Nursing', 3, 'Health First', 5, 'Personal Reasons', '2024-05-01'),
('Sophia Martinez', '1987-12-25', 'BEd', 5, 'EduWorld', 6, 'Relocation', '2024-01-20'),
('Benjamin Davis', '1991-04-11', 'BSc in Business Administration', 4, 'Retail Hub', 7, 'Career Growth', '2024-02-18'),
('Olivia Garcia', '1989-06-08', 'BSc in Civil Engineering', 7, 'Build It', 8, 'Career Change', '2024-03-25'),
('Lucas Thompson', '1994-03-12', 'Diploma in Automotive Technology', 3, 'AutoFix', 9, 'Better Opportunity', '2024-04-15'),
('Ava Moore', '1993-10-20', 'Diploma in Travel and Tourism', 2, 'Travel Experts', 10, 'Career Growth', '2024-05-05');

-- Insert data into the Employment table
INSERT INTO Employment (Start_Date, Applicant_ID, Vacancy_ID) VALUES
('2024-02-01', 1, 1),
('2024-03-01', 2, 2),
('2024-04-01', 3, 3),
('2024-05-01', 4, 4),
('2024-06-01', 5, 5),
('2024-02-15', 6, 6),
('2024-03-15', 7, 7),
('2024-04-15', 8, 8),
('2024-05-15', 9, 9),
('2024-06-15', 10, 10);
