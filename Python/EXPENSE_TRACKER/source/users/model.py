"""This module will contain all models related to users app
"""
import settings
import sqlite3
from common.model import DBModel

class UsersModel(DBModel):
    """This model will handle user related data transactions with DB
    """

    TABLE_NAME = "users"

    def __init__(self)->None:

        super().__init__()
        self.init_db()


    def init_db(self)->None:
        '''
        This function will create new database if it doesn't exict yet
        '''

        # self.con = sqlite3.connect(settings.DATABASE_PATH)
        # self.cur = self.con.cursor()

        sql = f'''
        CREATE TABLE IF NOT EXISTS {self.TABLE_NAME}
        (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT,
            password TEXT 
        )
        '''

        self.get_cur().execute(sql)


        self.get_con().commit()

    def admin_exists(self) ->bool:
        """Check if admin user exict in DB or not

        Returns:
            bool: True if admin already exists, otherwise return False
        """

        sql = f"SELECT * FROM {self.TABLE_NAME}"

        result = self.get_cur().execute(sql)

        if len(result.fetchall()):
            return True
        else:
            return False

    def create_admin(self, username: str, password: str)->None:
        """Create admin user in DB

        Args:
            username (str): admin username
            password (str): user password
        """

        sql = f'''
        INSERT INTO {self.TABLE_NAME} (username, password) VALUES ('{username}','{password}')
        '''
        # print(f"SQL Query: {sql}")
        self.get_cur().execute(sql)
        self.get_con().commit()


    def validate_admin(self, username: str, password: str)->bool:
        """This function will validate admin credentials

        Args:
            username (str): admin username
            password (str): admin password

        Returns:
            bool: return True if admin found otherwise return False
        """

        sql = f'''
        SELECT * FROM {self.TABLE_NAME} WHERE username='{username}' AND password='{password}'  
        '''

        result = self.get_cur().execute(sql)

        if len(result.fetchall()):
            return True
        else:
            return False

