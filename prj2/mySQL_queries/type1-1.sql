select distinct customer_id, package_id
from package natural join ( select package_id
							from loading natural join shipment
							where shipment.vehicle_id = '22222224'  and loading.is_visited=false) as accident
                            