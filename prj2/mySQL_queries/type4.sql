select customer_id, package_id, expected_arrive_date, actual_arrive_date
from package
where state='complete' and expected_arrive_date != actual_arrive_date