"""This module will contain all expense tracking models.
"""
import sqlite3
import settings
from common.model import DBModel

class ExpensesModel(DBModel):
    """This model will handle data transaction with expenses table
    """

    TABLE_NAME = "expenses"

    def __init__(self):
        """Model constructor
        """
        super().__init__()
        self.init_db()
    
    def init_db(self)->None:
        """This function will create the table in DB if it doesn't excist yet.
        """
       # self.con = sqlite3.connect(settings.DATABASE_PATH)
       # self.cur = self.con.cursor()
        sql = f'''
        CREATE TABLE IF NOT EXISTS {self.TABLE_NAME}
        (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        category TEXT,
        amount REAL,
        date TEXT
        )
        '''
        self.get_cur().execute(sql)
        self.get_con().commit()


    def create(self, category: str, amount: float, date: str)->None:
        """Insert new record in DB

        Args:
            category (str): expense category
            amount (float): expense amount
            date (str): expense date
        """

        sql = f'''
        INSERT INTO {self.TABLE_NAME} (category, amount, date) VALUES ('{category}','{amount}','{date}')
        '''
        self.get_cur().execute(sql)
        self.get_con().commit()


    def list(self)->list:
        """This function will retrieve all expenses from DB

        Returns:
            List: list of expenses
        """
        result = {}
        sql = f'''
        SELECT * FROM {self.TABLE_NAME}
        '''
        result = self.get_cur().execute(sql)
        return result.fetchall()

    def load_reports(self)->list:
        sql = f'''
        SELECT category, SUM(amount) AS total_amount, COUNT(id) AS total_records FROM {self.TABLE_NAME} GROUP BY category
        '''
        result = self.get_cur().execute(sql)
        return result.fetchall()





