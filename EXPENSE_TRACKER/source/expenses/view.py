"""This module will handle all manage expenses related views
"""
from typing import Dict
from datetime import date
from tabulate import tabulate

class ManageExpensesView:
    """This view will handle the menu options of manage expenses app
    """

    EXPENSE_CATEGORIES = [
    "Entertaiment",
    "Grocery",
    "Transportation",
    "Other"
]



    def menu_options(self)->int:
        """This view will display menu option to choose to add new expense or view the history

        Returns:
            int: selected menu option
        """

        print("### Manage expenses ###")
        print("1. Add new expense")
        print("2. View histoory")
        selected_menu = int(input("Enter menu option (1,2)"))
        return selected_menu

    def get_expense_info(self)->Dict:
        """This view will gather expense info from user

        Returns:
            Dict: expense info in dict format (category, amount, date)
        """
        data = {}
        print("### Add new expense record ###")
        print("Select expense category")

        for idx,value in enumerate(self.EXPENSE_CATEGORIES):
            print(f"\t{str(idx)}, {value}")

        category = int(input("Select Category from the list: "))
        data["category"] = self.EXPENSE_CATEGORIES[category]
        data["amount"] = float(input("Amount $: "))
        data["date"] = str(date.today())

        return data

    def display_expense_history(self, records: list)->None:
        """Display expense history

        Args:
            result (list): list of records
        """
        
        print(tabulate(records, headers = ["ID","Category","Amount $","Date"] ))

    def see_reports(self, reports: list)->None:
        """This view will display summary report

        Args:
            records (list): summary report data with key value pairs (category:total_amount)
        """

        print(tabulate(reports, headers = ["Category", "Total Amount $", "Qty"]))
