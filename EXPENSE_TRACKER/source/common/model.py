"""This module will contain model templates to be used in the app
"""
import settings
import sqlite3
from abc import ABC, abstractmethod


class DBModel(ABC):
    """This template will contain base db connection functionalities
    """
    def __init__(self)->None:
        self.__con = sqlite3.connect(settings.DATABASE_PATH)
        self.__cur = self.__con.cursor()

    @abstractmethod
    def init_db(self):
        pass

    def __del__(self)->None:
        self.__con.close()


    def get_cur(self):
        """Cursor getter

        Returns:
            _type_: Cursor
        """
        return self.__cur
    
    def get_con(self):
        """Connection getter

        Returns:
            _type_: Connection
        """
        return self.__con


